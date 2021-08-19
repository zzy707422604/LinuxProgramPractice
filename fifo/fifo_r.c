#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <fcntl.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int i=0,fd;
	char buf[4096];
	if(argc<2)
	{
		sys_err("Enter fifo name!\n");
	}
	fd = open(argv[1],O_RDONLY);
	if(fd==-1)
	{
		sys_err("Open fail!\n");
	}
	while(1)
	{
		int len = read(fd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,len);
		sleep(1);
	}
	
	return 0;
}
