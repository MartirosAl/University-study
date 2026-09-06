#include <stdio.h>    // puts(), printf(), perror(), getchar()
#include <stdlib.h>   // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // getpid(), getppid(),fork()
#include <sys/wait.h> // wait()

#define READ  0
#define WRITE 1

void child_a(int fd[]) {
  dup2(fd[1], 1);
  close(fd[0]);
  execlp("ls", "ls", "-F", "-1", NULL);
  exit(EXIT_SUCCESS);
}

void child_b(int fd[]) {
  dup2(fd[0], 0);
  close(fd[1]);
  execlp("nl", "nl", NULL);
  exit(EXIT_SUCCESS);
}

int main(void) {
  printf("Martirosyants Aleksandr 37 group \n");
  int fd[2];

  pid_t pid;
  pipe(fd); //организован канал
  switch (pid = fork()) {
    case -1:
      perror("fork failed");
      exit(EXIT_FAILURE);
    case 0: // процесс-потомок
      child_a(fd);
    default: //процесс-родитель

  }
  waitpid(pid, NULL, 0);

  switch (pid = fork()) {
  case -1:
    perror("fork failed");
    exit(EXIT_FAILURE);
  case 0: // процесс-потомок
    child_b(fd);
  default: //процесс-родитель
  
  }

  close(fd[0]);
  close(fd[1]);
  waitpid(pid, NULL, 0);
}
