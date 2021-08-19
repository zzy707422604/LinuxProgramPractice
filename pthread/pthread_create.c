#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <pthread.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void *ptf(void *arg)
{	
	printf("here is pthread! pid :%d, tid:%lu\n",getpid(),pthread_self());
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	tid = pthread_self();
	printf("here is main! pid :%d, tid:%lu\n",getpid(),tid);
	int ret = pthread_create(&tid,NULL,ptf,NULL);
	if(ret!=0)
	{
		sys_err("pthread_create fail!\n");
	}
	sleep(1);
	return 0;
}
