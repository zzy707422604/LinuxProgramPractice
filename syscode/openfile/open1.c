#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
int main(int argc, char *argv[])
{
	int fd;
	fd = open("./dict.c",O_RDONLY|O_CREAT|O_TRUNC,0644);//rw-r--r--
	printf("fd=%d\n",fd);
	fd = close(fd);
	printf("fd=%d\n",fd);
	return 0;
}
