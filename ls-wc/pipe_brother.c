#include <stdio.h>
#include <stdlib.h>
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
	int fd[2],i=0,n=2;
	pid_t pid;
	if(pipe(fd)==-1)
	{
		sys_err("pipe fail!\n");
	}

	for(;i<n;i++)
	{
		pid=fork();
		if(pid==0)
			break;
		else if(pid>0)
			continue;	
		else if(pid<0)
			sys_err("fork error!\n");
	}

	if(i==2)
	{
		//parent
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
	else if(i==0)
	{
		//second child
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		execlp("ls","ls",NULL);
		sys_err("execlp ls error!\n");//will not come backe when exec execlp unless error;
	}
	else if(i==1)
	{
		//first child
		int status;
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		wait(&status);
		execlp("wc","wc","-l",NULL);
		sys_err("execlp wc error!\n"); 
	}
	return 0;
}
