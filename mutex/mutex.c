#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <pthread.h>
pthread_mutex_t mutex;

void *ptf(void *arg)
{
	srand(time(NULL));	
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("hello ");
		sleep(rand()%3);
		printf("world\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	srand(time(NULL));
	int ret = pthread_mutex_init(&mutex,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"mutex init error:%s\n",strerror(ret));
		exit(1);
	}
	ret = pthread_create(&tid,NULL,ptf,NULL);
	if(ret!=0)
	{
		fprintf(stderr,"pthread_create error:%s\n",strerror(ret));
		exit(1);
	}
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("HELLO ");
		sleep(rand()%3);
		printf("WORLD\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
	pthread_join(tid,NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}
