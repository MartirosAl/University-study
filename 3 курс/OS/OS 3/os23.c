#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
const char *tempfile = "abc2"; 
void sighandler(int signum) {
    printf("Caught signal %d...\n", signum);
	unlink(tempfile);
	exit(0);
}
int main () {
	printf("Martirosyants Aleksandr 37 group \n");
	signal(SIGINT, sighandler);
	creat(tempfile, 0666);
	sleep(8);
	unlink(tempfile);
    return(0);
}

