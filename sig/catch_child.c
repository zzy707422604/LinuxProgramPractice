#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <signal.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

void catch_child(int signo)
{
	pid_t wpid;
	int status;
	while((wpid=waitpid(-1,&status,0))!=-1)//循环回收，防止僵尸进程
	{
			if(WIFEXITED(status))//判断是否正常退出
			{
				printf("catch child id%d, ret=%d\n",wpid,WEXITSTATUS(status));//打印回收的子进程id，同时获取回收时子进程退出的返回值
			}
	}
}

int main(int argc, char *argv[])
{
	//添加阻塞，避免捕捉函数在注册前 子进程就死亡发送信号
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGCHLD);
	sigprocmask(SIG_BLOCK,&set,NULL);

	pid_t pid;
	int i;
	for(i=0;i<15;i++)
	{
		if(fork()==0)//子进程时退出
		{
			break;
		}
	}
	if(i==15)//父进程
	{
		struct sigaction act;
		act.sa_handler=catch_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags=0;
		sigaction(SIGCHLD,&act,NULL);
		//回调函数注册完毕，解除阻塞
		sigprocmask(SIG_UNBLOCK,&set,NULL);
		printf("im parent, pid = %d\n",getpid());
		while(1);
	}
	else
	{
		printf("im child pid = %d\n",getpid());
		return i;
	}
	return 0;
}
