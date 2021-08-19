#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/wait.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

struct thrd
{
	int var;
	char str[256];
};

void *tfn(void *arg)
{
	struct thrd *tval;
	tval = malloc(sizeof(tval));
	tval->var = 100;
	strcpy(tval->str,"hello pthread");
	return (void*)tval;
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	struct thrd *retval;
	int ret = pthread_create(&tid,NULL,tfn,NULL);
	if(ret!=0)
	{
		sys_err("pthread_create error");
	}
	ret = pthread_join(tid,(void**)&retval);
	if(ret!=0)
		sys_err("pthread_join error");
	printf("child thread exit with var = %d,str=%s\n",retval->var,retval->str);
	sleep(10);
	pthread_exit(NULL);
}
