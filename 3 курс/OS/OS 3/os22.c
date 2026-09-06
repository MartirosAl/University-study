#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void sighandler(int signum) {
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);	
}
int main () {
   printf("Martirosyants Aleksandr 37 group \n");
   signal(SIGINT, sighandler);
   while(1);
   return(0);
}