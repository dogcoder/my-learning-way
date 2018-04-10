#include "head.h"

void sigfunc(int sig)
{
	printf("%d(SIGPIPE) is coming!\n",sig);
}

int send_n(int fd,char* file,int len)
{
	//signal(SIGPIPE,sigfunc);
	int totally=0;
	int num;
	while(totally<len)
	{
		num=send(fd,file+totally,len-totally,0);
		totally+=num;
	}
	return 0;
}


int recv_n(int fd, char*file,int len)
{
	int totally=0;
	int num;
	while(totally<len)
	{
		num=recv(fd,file+totally,len-totally,0);
		if(num==0)
		{
			printf("服务器断开！\n");
			return -1;
		}
		totally+=num;
	}
	return totally;
}


void sendcomd(char* comd ,char* arg,int socfd)
{
	int len;
	train file;
	bzero(&file,sizeof(file));
	//发送命令
	file.len=strlen(comd);
	strcpy(file.buf,comd);
	send_n(socfd,(char*)&file,4+file.len);
	printf("命令为：%s\n",comd);
	//发送命令参数
	bzero(&file,sizeof(file));
	file.len=strlen(arg);
	strcpy(file.buf,arg);
	send_n(socfd,(char*)&file,4+file.len);
	printf("参数为：%s\n",arg);
}

void sendcomd1(char* comd ,int socfd)
{
	int len;
	train file;
	bzero(&file,sizeof(file));
	//发送命令
	file.len=strlen(comd);
	strcpy(file.buf,comd);
	send_n(socfd,(char*)&file,4+file.len);
	printf("sendcomd1为：%s\n",comd);
}

void recvcomd1(char* comd,int socfd)
{
	int len1;
	recv_n(socfd,(char*)&len1,sizeof(len1));	//接受命令 或用户名
	recv_n(socfd,comd,len1);
}
