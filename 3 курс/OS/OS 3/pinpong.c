#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_CNT 10
int target_pid, cnt;
int fd[2];
int status;
void SigHndlr(int s){
	// � ��ࠡ��稪� ᨣ���� �ந�室�� � �⥭�� � ������
	signal(SIGUSR1, SigHndlr);
	if (cnt < MAX_CNT){
		read(fd[0], &cnt, sizeof(int));
		if (target_pid == getppid())
			printf("child %d send %d \n", getpid(), cnt);
		else
			printf("parent %d send %d \n", getpid(), cnt);
		cnt++;
		write(fd[1], &cnt, sizeof(int));
		// ���뫠�� ᨣ��� ��஬�, ��� ���� �� ������
		
			
		kill(target_pid, SIGUSR1);
	}
	else
		if (target_pid == getppid()){
		// �᫮��� ����砭�� ���� �஢������ ��⮬���
		printf("Child is going to be terminated\n");
		close(fd[1]);
		close(fd[0]);
		// �����蠥��� ��⮬��
		exit(0);
		}
		else
			kill(target_pid, SIGUSR1);
}
int main(int argc, char **argv){
	printf("Martirosyants Aleksandr 37 group \n");
	pipe(fd); 
	signal (SIGUSR1, SigHndlr);	//��ࠡ��稪 ᨣ����� ��� ����� ����ᮢ
	cnt = 0;
	if (target_pid = fork()){
		wait(&status); //த�⥫� ���� �����襭�� ��⮬��
		printf("Parent is going to be terminated\n");
		close(fd[1]); close(fd[0]);
		return 0;
	}
	else{
		target_pid = getppid(); // pid த�⥫�
		write(fd[1], &cnt, sizeof(int));
		kill(target_pid, SIGUSR1);
		for(;;);
	}
}
