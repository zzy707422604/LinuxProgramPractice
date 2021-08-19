#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char *argv[])
{

	pid_t pid = fork();
	if(pid == 0)
	{
		//execlp("ls","-l","-h",NULL); wrong
		execlp("ls","ls","-l","-h",NULL);
		perror("exec error");
		exit(1);
	}	
	else if (pid == -1)
	{
		printf("Child process create fail\n");
	}
	else
	{
		sleep(1);
		printf("Here is parent process! The child pid is : %d\n",pid);
	}

        return 0;
}  
