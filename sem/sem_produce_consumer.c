#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <semaphore.h>
#define NUM 5
sem_t product_num,blank_num;
int queue[NUM];
void err_thread(int ret,char *str)
{
	if(ret!=0)
	{
		fprintf(stderr,"%s:%s\n",str,strerror(ret));
		pthread_exit(NULL);
	}
}

void *consumer(void *arg)
{
	int i = 0;
	while(1)
	{
		sem_wait(&product_num);
		printf("----consumer consuming : %d\n",queue[i]);
		queue[i]=0;
		sem_post(&blank_num);
		i=(i+1)%NUM;
		sleep(rand()%3);
		
	}
	return NULL;
}

void *producer(void *arg)
{
	int i=0;
	while(1)
	{
		sem_wait(&blank_num);
		queue[i]=rand()%1000+1;
		printf("producer producing : %d\n",queue[i]);
		sem_post(&product_num);
		i=(i+1)%NUM;
		sleep(rand()%1);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int ret;
	pthread_t pid,cid;
	srand(time(NULL));
	sem_init(&product_num,NULL,0);
	sem_init(&blank_num,NULL,NUM);
	ret = pthread_create(&pid,NULL,producer,NULL);
	if(ret != 0)
	{
		err_thread(ret,"pthread_create producer fail!");	
	}
	ret = pthread_create(&cid,NULL,consumer,NULL);
	if(ret != 0)
	{
		err_thread(ret,"pthread_create consumer fail!");	
	}
	
	pthread_join(pid,NULL);
	pthread_join(cid,NULL);

	sem_destroy(&product_num);
	sem_destroy(&blank_num);
	return 0;
}
