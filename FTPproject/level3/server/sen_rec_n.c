#include "head.h"


int send_n(int fd,char* file,int len)
{
	signal(SIGPIPE,SIG_IGN);
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
		if(num==0){
			return -1;
		}
		totally+=num;
	}
	return 1;
}

int sendfile_n(int socfd,int fd,size_t size)
{
	size_t totally=0;
	size_t num;
	while(totally<size)
	{
		num=sendfile(socfd,fd,NULL,size-totally);
		if(num==0)
		{
			return totally;
			break;
		}
		if(num==-1)
		{
			return -1;
		}
		totally+=num;
	}
	return 1000;
}

