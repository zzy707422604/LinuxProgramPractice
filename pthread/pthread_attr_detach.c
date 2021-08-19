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
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	pthread_attr_t attr;

	int ret = pthread_attr_init(&attr);
	if(ret!=0)
	{
		fprintf(stderr,"pthread_attr_init fail!%s\n",strerror(ret));
		exit(1);
	}
	
	ret = pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if(ret!=0)
	{
		fprintf(stderr,"pthread_setdetachstate fail!%s\n",strerror(ret));
		exit(1);
	}

	ret = pthread_create(&tid,&attr,ptf,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"pthread_create fail!%s\n",strerror(ret));
		exit(1);
	}
	
	ret = pthread_attr_destroy(&attr);
	if(ret!=0)
	{
		fprintf(stderr,"pthread_attr_destroy fail!%s\n",strerror(ret));
		exit(1);
	}
	
	sleep(1);//让子线程先跑
	
	ret = pthread_join(tid,NULL);
	printf("join ret : %d\n",ret);
	if(ret!=0)
	{
		fprintf(stderr,"pthread_join fail!%s\n",strerror(ret));
		exit(1);
	}
	tid = pthread_self();
	printf("here is main! pid :%d, tid:%lu\n",getpid(),tid);
	pthread_exit((void*)0);
}
