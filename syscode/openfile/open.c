#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[])
{
	int fd;
	fd = open("./dict2.c",O_RDONLY);//rw-r--r--
	printf("fd=%d\n,errno = %d:%s\n",fd,errno,strerror(errno));
	fd = close(fd);
	printf("fd=%d\n",fd);
	return 0;
}
