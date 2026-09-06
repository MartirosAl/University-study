#include "parser.h"

#include <unistd.h>  // STDIN_FILENO, STDOUT_FILENO
#include <stdlib.h>  // EXIT_FAILURE
#include <stdio.h>   // printf()
#include <string.h>  // strlen()
#include <ctype.h>   // isspace(),
#include <string.h>  // strtok_r()
#include <stdbool.h> // true, false
#include <string.h>



void remove_history_entry(cmd_hist* cmd_history, size_t cmd_idx)
{
  free(cmd_history->history[cmd_idx]);
}



void add_history_entry(cmd_hist* cmd_history, char* cmd)
{
  size_t hist_idx = (cmd_history->oldest_cmd_idx + cmd_history->count) % MAX_HIST;

  if (cmd_history->count == MAX_HIST)
  {
    remove_history_entry(cmd_history, hist_idx);
  }

  size_t len = strlen(cmd) + 1;
  cmd_history->history[hist_idx] = (char*)malloc(len * sizeof(char));
  if (!cmd_history->history[hist_idx])
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  strcpy(cmd_history->history[hist_idx], cmd);

  if (cmd_history->count == MAX_HIST)
  {
    cmd_history->oldest_cmd_idx = (cmd_history->oldest_cmd_idx + 1) % MAX_HIST;
  }
  else
  {
    ++cmd_history->count;
  }
}



char* get_history_entry(cmd_hist* cmd_history, size_t entry_idx)
{
  if (cmd_history->count == 0 || entry_idx == 0 || entry_idx > cmd_history->count)
  {
    return NULL;
  }

  size_t len = strlen(cmd_history->history[entry_idx - 1]) + 1;
  char* res_cmds = (char*)malloc(len * sizeof(char));
  if (!res_cmds)
  {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  strcpy(res_cmds, cmd_history->history[entry_idx - 1]);

  return res_cmds;
}



bool empty(char* str)
{
  while (*str)
  {
    if (!isspace(*str++))
    {
      return false;
    }
  }

  return true;
}



char* ltrim(char* s)
{
  while (isspace((int)*s))
  {
    ++s;
  }

  return s;
}



char* rtrim(char* str)
{
  if(*str == 0 )
  {
    return str;
  }
  else
  {
    char* back = str + strlen(str) - 1;

    while(isspace(*back))
    {
      back--;
    }

    *(back+1) = '\0';

    return str;
  }
}



char* trim(char* str)
{
  if (str != NULL)
  {
    return(ltrim(rtrim(str)));
  }
  else
  {
    return NULL;
  }
}



void get_argv(char* str, const char* delimiter, char* argv[])
{
  char *token;
  int i = 0;

  /* получаем первый токен */
  token = strtok(str, delimiter);

  /* идем по другим токенам */
  while( token != NULL )
  {
    argv[i] = token;
    token = strtok(NULL, delimiter);
    i++;
  }

  argv[i] = NULL;
}



char* position_to_string(position_codes pos)
{

  switch (pos)
  {
  case single:
    return "single";
  case first:
    return "first";
  case middle:
    return "middle";
  case last:
    return "last";
  case unknown:
    return "unknown";
  }
}



void print_argv(char* argv[])
{
  int i = 0;
  char* s;

  while ((s = argv[i]))
  {
    printf("  argv[%d] = %s\n", i, s);
    i++;
  }
}



void print_commands(cmd_t* cmds_array, size_t n)
{
  for (size_t i = 0; i < n; ++i)
  {
    printf("==> commands[%lu]\n", i);
    printf("  pos = %s\n", position_to_string(cmds_array[i].pos));

    print_argv(cmds_array[i].argv);
  }
}



void print_history(const cmd_hist* cmd_history)
{ 
  printf("\n") ;
  for (size_t i = 0; i < cmd_history->count; ++i)
  {
    printf("History entry[%lu]: ", i);
    printf("%s\n", cmd_history->history[i]);
    printf("\n");
  }
}



void parse_cmds(char* str, const char* delimiter, char* cmds[])
{
  char *token;
  int i = 0;

  token = strtok(str, delimiter);

  if (token == "!!!")
  {
    
  }

  while( token != NULL )
  {
    if (empty(token))
    {
      fprintf(stderr, "Parser error: EMPTY command!\n");
      exit(EXIT_FAILURE);
    }

    cmds[i] = trim(token);
    token = strtok(NULL, delimiter);
    i++;
  }

  cmds[i] = NULL;
}



position_codes cmd_position(size_t cmd_index, size_t cmds_amount)
{
  if (cmd_index == 0 && cmds_amount == 1)
  {
    return single;
  }
  else if (cmd_index == cmds_amount - 1)
  {
    return last;
  }
  else if (cmd_index == 0 && cmds_amount > 1)
  {
    return first;
  }
  else if (cmd_index > 0 && cmd_index < cmds_amount)
  {
    return middle;
  }
  else
  {
    return unknown;
  }
}



size_t first_pass(char *str, cmd_t* cmds_array)
{
  char* cmds[MAX_COMMANDS];

  parse_cmds(str, "|", cmds);

  int i = 0;

  while (cmds[i])
  {
    cmds_array[i].pos = unknown;
    get_argv(cmds[i], " ", cmds_array[i].argv);
    i++;
  }

  return i;
}



void second_pass(cmd_t* cmds_array, size_t cmds_amount)
{
  for (int i = 0; i < cmds_amount; i++)
  {
    cmds_array[i].pos = cmd_position(i, cmds_amount);
  }
}



int parse_commands(char *str, cmd_t* cmds_arr, cmd_hist* history)
{
  add_history_entry(history, str);

  int cmds_amount = first_pass(str, cmds_arr);

  second_pass(cmds_arr, cmds_amount);

  return cmds_amount;
}