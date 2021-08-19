#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
	int fd1 = open(argv[1],O_RDWR);
	int fd2 = open(argv[2],O_RDWR);

	dup2(fd1,fd2);

	write(fd2,"1234567",7);

	dup2(fd1,STDOUT_FILENO);
	printf("888");

	return 0;
}
