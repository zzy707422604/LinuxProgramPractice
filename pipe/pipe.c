#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
	int fd[2];
	int ret = pipe(fd);
	char *str="hello pipe\n";
	char buf[1024];
	if(ret==0)
	{
		printf("pipe success!\n");
		pid_t pid = fork();
		if(pid>0)
		{
			//parent
			printf("parent now !\n");
			close(fd[0]);//close read
			write(fd[1],str,strlen(str));
			close(fd[1]);
			int status;
			printf("finish parent work ,wait now\n");
			wait(&status);
			printf("parent die now\n");
		}
		else if(pid==0)
		{
			//child
			printf("child now !\n");
			close(fd[1]);//close write
			ret = read(fd[0],&buf,sizeof(buf));
			write(STDOUT_FILENO,buf,ret);
			close(fd[0]);
			printf("finish child work, child die now\n");
		}
		else
		{
			perror("fork fail");
			exit(1);
		}		
	}
	else if(ret==-1)
	{
		perror("pipe file");
		exit(1);
	}
}
