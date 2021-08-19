#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
struct msg
{
	int num;
	struct msg *next;
};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_data = PTHREAD_COND_INITIALIZER;
struct msg *head;
void err_thread(int ret,char *str)
{
	while(1)
	{
		if(ret!=0)
		{
			fprintf(stderr,"%s:%s\n",str,strerror(ret));
			pthread_exit(NULL);
		}
	}
}

void *consumer(void *arg)
{
	struct msg *mp;
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(head==NULL)//用while而不用if是怕都多个消费者时，信号通知了却被其他消费者消费了
		{
			pthread_cond_wait(&has_data,&mutex);
		}
		mp = head;
		head = mp->next;
		printf("consumer consuming! shared data : %d\n",mp->num);
		pthread_mutex_unlock(&mutex);
		free(mp);
		sleep(rand()%3);
	}
	return NULL;
}

void *producer(void *arg)
{
	struct msg *mp;
	while(1)
	{
		mp = malloc(sizeof(struct msg));
		mp->num = rand() % 1000 + 1;
		printf("producer producing! shared data : %d\n",mp->num);
		pthread_mutex_lock(&mutex);
		mp->next = head;
		head = mp;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&has_data);
		sleep(rand()%3);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t pid,cid;
	int ret;
	srand(time(NULL));
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
	return 0;
}
