#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void *tfn(void *arg)
{
	while(1)
	{
	printf("child thread!process id:%d, thread id:%lu\n",getpid(),pthread_self());
	}
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	pthread_create(&tid,NULL,tfn,NULL);
	
	sleep(5);
	pthread_cancel(tid);
	while(1);
	return 0;
}
