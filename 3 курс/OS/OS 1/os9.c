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
		printf("Child (%d): session %d\n", getpid(), getsid(child));
	}
	else 
	{	
		int parent = getpid();
		wait(NULL);
		printf("Parent(%d): session %d\n", getpid(), getsid(parent));
	}
	return 0;
}

	

