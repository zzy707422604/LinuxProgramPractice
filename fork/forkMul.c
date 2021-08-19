#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[])
{

	int n = atoi(argv[1]);//创建多少个子进程
	int sum = n;
	pid_t pid;
	while (n>0)
	{
		pid = fork();
		sleep(1);
		if(pid == 0)
		{
			break;
		}	
		else if (pid == -1)
		{
			printf("Child process create fail\n");
		}
		else
		{
			printf("Here is parent process! The %dth child pid is : %d\n",(sum-n+1),pid);
		}
		n--;
	}
	if(n==0)
	{
		sleep(1);
		printf("I'm parent\n");
	}
	else
	{
	printf("I'm %dth child\n",sum-n+1);
	}
	printf("=================================================end file\n");
        return 0;
}  
