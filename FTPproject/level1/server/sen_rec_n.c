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
