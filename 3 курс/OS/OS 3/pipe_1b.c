#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h> 
void pipe_handler(int sig) 
{
    write(STDERR_FILENO, "pipe handler called: SIGPIPE received (13)\n", 43);
    exit(EXIT_FAILURE);
}
int main(int argc, char **argv){
	printf("Martirosyants Aleksandr 37 group \n");
	signal(SIGPIPE, pipe_handler);
	char *s = "Hello!";
	char buf;
	int pipes[2];
	pipe(pipes);
	close(pipes[0]);
	write(pipes[1], s, strlen(s) + 1);
	close(pipes[1]);
	while (read(pipes[0], &buf, 1) > 0) {
      write(STDOUT_FILENO, &buf, 1); // read in data 1 char at a time)
    }
	write(STDOUT_FILENO, "\n", 1);
	close(pipes[0]);
	return 0;
}
