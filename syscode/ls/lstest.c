#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/stat.h>
#define PATH_LEN 256
void isFile(char* name);
void fetchdir(const char* dir,void(*fcn)(char*))
{
	char name[PATH_LEN];
	struct dirent *sdp;
	DIR *dp;
	if((dp=opendir(dir))==NULL)
	{
		//打开目录失败
		fprintf(stderr,"fetchdir:can't open %s\n",dir);
		return;
	}
	
	while((sdp=readdir(dp))!=NULL)
	{
		//判断是否是.或者.. 否则会陷入死循环
		if(strcmp(sdp->d_name,".")==0
		||strcmp(sdp->d_name,"..")==0)
		{
			continue;
		}
		//判断是否超出名字长度,+2是/0
		if(strlen(dir)+strlen(sdp->d_name)+2>PATH_LEN)
		{
			fprintf(stderr,"fetchdir:path %s %s too long\n"
			,dir,sdp->d_name);
			return;
		}
		else
		{
			sprintf(name,"%s/%s",dir,sdp->d_name);
			(*fcn)(name);//回调函数再调isFile
		}

	}
	closedir(dp);
	return;
}

void isFile(char* name)
{
	struct stat sbuf;
	if(stat(name,&sbuf)==-1)
	{
		//获取失败
		fprintf(stderr,"isFile: can't access %s\n",name);
	}
	if((sbuf.st_mode&S_IFMT)==S_IFDIR)
	{
		//是文件夹
		fetchdir(name,isFile);//会调函数
	}
	printf("%8ld %s\n",sbuf.st_size,name);
	//不是文件夹就打印文件大小和名字
	return;
}

int main(int argc, char *argv[])
{
	if(argc==1)
	{
		isFile(".");
	}
	else
	{
		isFile(argv[1]);
	}
	return 0;
}
