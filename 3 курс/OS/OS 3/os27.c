#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
int volatile done = 0;
void handler(int sig, siginfo_t *siginfo, void *context){
	printf("Сигнал %d был перехвачен\n", sig);
	printf("your UID is %d\n", siginfo->si_uid);
	printf("your PID is %d\n", siginfo->si_pid);
	done = 1;
}
int main(){
	printf("Martirosyants Aleksandr 37 group \n");
	int pid = getpid();
	printf("Ладно, поехали — убей меня (%d), и я скажу тебе, кто ты.\n", pid);
	//  используем более расширенный обработчик `sigaction`
    struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	if (sigaction(SIGINT, &sa, NULL)!=0){
		return(1);
	}

	while(!done){
	}
	printf("Вот, видишь!\n");
	return(0);
}

