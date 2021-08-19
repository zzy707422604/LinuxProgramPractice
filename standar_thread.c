#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
void err_thread(int ret,char *str)
{
	if(ret!=0)
	{
		fprintf(stderr,"%s:%s\n",str,strerror(ret));
		pthread_exit(NULL);
	}
}

int main(int argc, char *argv[])
{
	return 0;
}
