#include <stdio.h>   // puts(), printf()
#include <signal.h>  // SIGFPE, SIGSEGV, SIGINT
#include <stdlib.h>  // exit(), EXIT_SUCCESS, EXIT_FAIURE
#include <unistd.h>  // getpid(), pause()
#include <stdbool.h> // true, false

sig_atomic_t volatile done = false;

int divide_by_zero() {
  int a = 1;
  int b = 0;
  return a / b;
}

void segfault() {
  int *ptr = NULL;
  *ptr = 42;
}

void signal_handler(int s) {
  switch(s) {
    case SIGFPE:
      fputs("SIGFPE: арифметическое исключение, например, деление на ноль.\n", stderr);
      exit(EXIT_FAILURE);
    case SIGSEGV:
      fputs("SIGSEGV: segfault.\n", stderr);
      exit(EXIT_FAILURE);
      break;
    case SIGINT:
      fputs("SIGINT: Прерывание выполнения по нажатию Ctrl-C.\n", stderr);
	  done = true;
      break;
    case SIGUSR1:
      puts("Hello!");
      break;
  }
}

int main(void) {
	
  printf("Martirosyants Aleksandr 37 group \n");
  printf("My PID = %ld\n", (long) getpid());
  
  // Установите обработчики сигналов.
  
  signal(SIGFPE,  signal_handler);
  signal(SIGSEGV, signal_handler);
  signal(SIGINT,  signal_handler);
  signal(SIGUSR1, signal_handler);
  //divide_by_zero();
  
  //segfault();
  
  // Подождите, пока не поступит сигнал.
  
  //pause();
  while (pause()){
	  if (done) break;
  }
  
  puts("Well done!");
  
  exit(EXIT_SUCCESS);
}
