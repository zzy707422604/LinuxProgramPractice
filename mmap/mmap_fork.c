#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}
int var=100;
int main(int argc, char *argv[])
{
	int *p;
	int fd;
	pid_t pid;
	fd = open("mmaptest",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd==-1)
	{
		sys_err("open error!\n");
	}
	ftruncate(fd,20);
	int len = lseek(fd,0,SEEK_END);
	p = mmap(NULL,len,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
	{
		sys_err("mmap fail!\n");
	}
	close(fd);
	pid = fork();
	if(pid<0)
	{
		sys_err("fork fail!\n");
	}
	else if(pid==0)
	{
		//child
		*p = 2000;
		var = 1000;
		printf("child:*p=%d,var=%d\n",*p,var);
	}
	else if(pid>0)
	{
		//parent
		wait(NULL);
		printf("parent:*p=%d,var=%d\n",*p,var);
		int ret = munmap(p,len);
		if(ret==-1)
		{
			sys_err("munmap fail!\n");
		}
	}
		
	return 0;
}
