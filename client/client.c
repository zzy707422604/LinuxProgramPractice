#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>//toupper
#include <sys/socket.h>
#include <arpa/inet.h>//socket_addr

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8888

void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	//创建socket
	int cfd;
	int ret;
	cfd = socket(AF_INET,SOCK_STREAM,0);
	if(cfd==-1)
	{
		sys_err("socket create error");
	}
	//创建连接
	struct sockaddr_in server_sock;//服务器地址结构
	server_sock.sin_family=AF_INET;
	server_sock.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET,SERVER_ADDR,&server_sock.sin_addr.s_addr);
	ret = connect(cfd,(struct sockaddr *)&server_sock,sizeof(server_sock));
	if(ret!=0)
	{
		sys_err("connect error");
	}
	//循环写读
	int i = 10;
	char buf[BUFSIZ];
	while(--i)
	{
		write(cfd,"hello\n",6);	
		ret = read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,ret);
		sleep(1);
	}

	close(cfd);
	
	return 0;
}
