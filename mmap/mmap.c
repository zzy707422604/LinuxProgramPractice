#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int fd;
	char *p;
	fd = open("mmaptest",O_RDWR|O_CREAT|O_TRUNC,0644);
	if(fd==-1)
	{
		sys_err("open error!\n");
	}
	ftruncate(fd,20);//enlarge
	int len = lseek(fd,0,SEEK_END);
	p = mmap(NULL,len,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(p==MAP_FAILED)
	{
		sys_err("map error");
	}
	strcpy(p,"hello map!\n");
	printf("%s",p);
	munmap(p,len);
	return 0;
}
