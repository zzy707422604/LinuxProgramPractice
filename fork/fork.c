#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
 	printf("before fork1 \n");	
 	printf("before fork2 \n");	
 	printf("before fork3 \n");	
 	printf("before fork4 \n");

	pid_t pid = fork();
	if(pid == 0)
	{
		printf("Here is child process! The child process is created\n");
	}	
	else if (pid == -1)
	{
		printf("Child process create fail\n");
	}
	else
	{
		printf("Here is parent process! The child pid is : %d\n",pid);
	}

	printf("=================================================end file\n");
        return 0;
}  
