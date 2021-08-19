#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
pthread_rwlock_t rwlock;
int counter=0;
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void *th_read(void *arg)
{
	while(1)
	{
		pthread_rwlock_rdlock(&rwlock);
		printf("read: %d-th,pthreadID:%lu,counter:%d\n",(int)arg,pthread_self(),counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(2000);
	}
}

void *th_write(void *arg)
{
	int before;
	while(1)
	{
		pthread_rwlock_wrlock(&rwlock);
		usleep(1000);
		before = counter;
		printf("write:%d-th,pthreadID:%lu,before:%d,counter:%d\n",(int)arg,pthread_self(),before,++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(10000);
	}
}

int main(int argc, char *argv[])
{
	int i = 0;
	pthread_t tid[8];
	pthread_rwlock_init(&rwlock,NULL);
	for(;i<3;i++)
	{
		pthread_create(&tid[i],NULL,th_read,(void*)i);
	}
	for(;i<8;i++)
	{
		pthread_create(&tid[i],NULL,th_write,(void*)i);
	}
	for(;i>0;i--)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_rwlock_destroy(&rwlock);
	pthread_exit(NULL);
}
