#include "parser.h"    // cmd_t, position_codes, parse_commands()

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>     //fcntl(), F_GETFL
#include <sys/wait.h>



cmd_t commands[MAX_COMMANDS];
pid_t pids[MAX_COMMANDS];
cmd_hist history;



int fd[2];



void fork_commands(int n)
{
  // "Инициализируем" предыдущий канал.
  int prev_pipe[2] = {-1, -1};

  for (int i = 0; i < n; i++)
  {
    // "Инициализируем" текущий канал.
    int cur_pipe[2] = {-1, -1};

    // Если команда не последняя, то делаем новый канал.
    if (commands[i].pos != last && commands[i].pos != single)
    {
      if (pipe(cur_pipe) == -1)
      {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
      }
    }

    pid_t pid = fork();

    if (pid == -1)
    {
      perror("Fork failed");
      exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
      // Если команда не первая, то перенаправляем вход с предыдущего канала.
      if (commands[i].pos != first && commands[i].pos != single)
      {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
        close(prev_pipe[1]);
      }

      // Если команда не последняя, то перенаправляем выход на текущий канал.
      if (commands[i].pos != last && commands[i].pos != single)
      {
        dup2(cur_pipe[1], STDOUT_FILENO);
        close(cur_pipe[0]);
        close(cur_pipe[1]);
      }
      
      execvp(commands[i].argv[0], commands[i].argv);

      fprintf(stderr, "shell: command not found: %s\n", commands[i].argv[0]);
      exit(EXIT_FAILURE);
    }
    else
    {
      // Если команда не первая, то существует предыдущий канал. Закрываем оба его конца.
      if (commands[i].pos != first && commands[i].pos != single)
      {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
      }

      prev_pipe[0] = cur_pipe[0];
      prev_pipe[1] = cur_pipe[1];
    }
  }
}



void get_line(char* buffer, size_t size)
{
  size_t a = getline(&buffer, &size, stdin);
  buffer[strlen(buffer)-1] = '\0';
}



void wait_for_all_cmds(int n)
{
  for (int i = 0; i < n; ++i)
  {
    waitpid(pids[i], NULL, 0);
  }
}



int main()
{
  int n;               // Количество команд в конвейере команд.
  size_t size = 128;   // Максимальный размер командной строки.
  char line[size];     // Буфер для командной строки.

  while(true)
  {
    printf(" >>> ");

    get_line(line, size);

    if (line[0] == '!')
    {
      int hist_idx = atoi(line + 1);

      char* recived_cmds = get_history_entry(&history, hist_idx);
      if (!recived_cmds)
      {
        printf("\nHistory is empty or invalid index entered.\n\n");
        continue;
      }

      n = parse_commands(recived_cmds, commands, &history);
    }
    else if (line == "exit")
    {
      for (size_t i = 0; i < history.count; ++i)
      {
        free(history.history[i]);
      }

      exit(EXIT_SUCCESS);
    }
    else
    {
      n = parse_commands(line, commands, &history);
    }
    
	  print_history(&history);
    fork_commands(n);

    wait_for_all_cmds(n);
  }

  exit(EXIT_SUCCESS);
}