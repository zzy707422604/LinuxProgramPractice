#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd;
	pid = fork();
	if(pid>0)
	{
		exit(0);
	}
	pid = setsid();//创建新会话
	chdir("/home/zzy/Desktop/test/daemon/daemonWockDir");
	umask(0022);
	close(STDIN_FILENO);
	fd = open("/dev/null",O_RDWR);
	dup2(fd,STDOUT_FILENO);
	dup2(fd,STDERR_FILENO);
	while(1);
	return 0;
}
