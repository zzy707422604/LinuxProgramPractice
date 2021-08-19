#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
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
	fd = open(argv[1],O_WRONLY);
	if(fd==-1)
	{
		sys_err("Open fail!\n");
	}
	while(1)
	{
		sprintf(buf,"hello,itcast:%d\n",i++);
		write(fd,buf,strlen(buf));
		sleep(1);
	}
	close(fd);
	return 0;
}
