#define _GNU_SOURCE // to define REG_RIP
#include <stdio.h>
#include <signal.h>
#include <ucontext.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
static void handler(int sig_no, siginfo_t *info, void *cntx){
	ucontext_t *context = (ucontext_t *) cntx;
	unsigned long pc = context->uc_mcontext.gregs[REG_RIP];
	printf("Illegal instruction at 0x%lx value 0x%x\n", pc , *(int*)pc);
	context->uc_mcontext.gregs[REG_RIP] = pc+2;
}
int main(){
	printf("Martirosyants Aleksandr 37 group \n");
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGSEGV, &sa, NULL);
	printf("Let's go!\n");
	foo: 
	asm(".word 0x00000000");
	foo2: 
	printf("Label foo %p!\n", &&foo);
	printf("Label foo2 %p!\n", &&foo2);
	return 0 ;
}
