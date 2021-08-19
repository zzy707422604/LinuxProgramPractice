#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>//toupper
#include <sys/socket.h>
#include <arpa/inet.h>//socket_addr
#define SERVER_PORT 8888
#define LISTEN_MOST 128
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
//创建套接字
	int lfd = 0;//套接字文件描述符
	lfd = socket (AF_INET,SOCK_STREAM,0);//AF_INET:ipv4,SOCK_STREAM:套接字协议（TCP） 0:套接字通信协议（TCP）
	if(lfd==-1)
	{
	  sys_err("创建套接字失败");
	}

//绑定套接字
	int ret;
	struct sockaddr_in server_addr;//服务器地址空间
	server_addr.sin_family = AF_INET;//协议
	server_addr.sin_port = htons(SERVER_PORT);//端口
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//自动获取ip地址
	ret = bind(lfd,(struct sockaddr *)&server_addr,sizeof(server_addr));//绑定
	if(ret==-1)
	{
	  sys_err("绑定套接字失败");
	}
//设置监听上限
	ret = listen(lfd,LISTEN_MOST);
	if(ret==-1)
	{
	  sys_err("设置监听上限失败");
	}
//阻塞连接
	struct sockaddr_in client_addr;//客户端地址空间
	socklen_t client_addr_len=sizeof(client_addr);//客户端地址空间长度
	int cfd;//用于连接的套接字文件描述符
	cfd = accept(lfd,(struct sockaddr *)&client_addr,&client_addr_len);//阻塞监听，返回一个新的文件描述符号
	//打印客户端ip地址和端口号
	char clientIP[BUFSIZ];
	printf("IP addr:%s ,port%d\n",
inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,clientIP,sizeof(clientIP)),
	ntohs(client_addr.sin_port));

	if(cfd==-1)
	{
	  sys_err("accept error");
	}
//读取文件
	char buf[BUFSIZ];//读取缓存
	while(1)
	{
		int byteNum;//读取到的字节数
		byteNum=read(cfd,buf,sizeof(buf));
		write(STDOUT_FILENO,buf,byteNum);
//将小写转换为大写
		for(int i = 0; i<byteNum; i++)
		{
		  buf[i]=toupper(buf[i]);
		}
//输出写出到buf
		write(cfd,buf,byteNum);
			
	}
	close(lfd);
	close(cfd);
return 0;
}
