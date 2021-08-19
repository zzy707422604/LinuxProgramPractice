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

int main(int argc, char *argv[])
{
	sigset_t set, oldset, pedset;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGBUS);
	sigaddset(&set,SIGKILL);
	sigprocmask(SIG_BLOCK,&set,&oldset);
	while(1)
	{
		sigpending(&pedset);
		int i;
		for(int i=1;i<32;i++)
		{
			if(sigismember(&pedset,i))
				putchar('1');
			else
				putchar('0');
		}
		printf("\n");
		sleep(1);
	}
	return 0;
}
