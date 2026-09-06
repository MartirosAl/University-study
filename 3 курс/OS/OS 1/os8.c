#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() 
{
	  printf("Martirosyants Aleksandr Evgenievich 37 group \n");
	  
	int pid = fork();
	if (pid == 0)
	{
		int child = getpid();
		printf("Child (%d): parent %d, group %d\n", getpid(), getppid(), getpgid(child));
		sleep(10);
		printf("Child(%d): parent %d, group %d\n", getpid(), getppid(), getpgid(child));
		//sleep(4);
		//printf("Child(%d): parent %d, group %d\n", getpid(), getppid(), getpgid(child));
	}
	else 
	{	
		int parent = getpid();
		printf("Parent(%d): parent %d, group %d\n", getpid(), getppid(), getpgid(parent));
		sleep(4);
		int zero = 0;
		int u = 5 / zero;
	}
	return 0;
}
