#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
char global[] = "This is a global string";
int c;
int a = 5;
const int b = 5;
int main ()
 {
		printf("Martirosyants Aleksandr 37 group\n");
	int pid = getpid();
	foo:
	printf("process id: %d\n", pid);
	printf("global string: %p\n", &global);
	printf("main() is: %p\n", (void*)main);
	printf("the code: %p\n", &&foo);
	printf("int a=5; is: %p\n", &a);
	printf("int c; is: %p\n", &c);
	printf("const int b is: %p\n", &b);
	printf("\n\n /proc/%d/maps \n\n", pid);
	char command [50];
	sprintf(command, "cat /proc/%d/maps", pid);
	system(command);
	return 0;
}
