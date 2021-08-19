#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <signal.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void sig_catch(int signo) //call back
{
	if(signo==2)
		printf("catch SIGINT %d\n",signo);
	else if(signo ==3)
		printf("catch SIGQUIT %d\n",signo);
	
	return;
}

int main(int argc, char *argv[])
{
	struct sigaction act , oldact;
	act.sa_handler = sig_catch;//set callback
	sigemptyset(&(act.sa_mask));// clean sa_mask
	act.sa_flags=0;//usually use
	sigaction(SIGINT,&act,&oldact);
	sigaction(SIGQUIT,&act,&oldact);
	while(1);
	return 0;
}
