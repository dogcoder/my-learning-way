#include "head.h"


int recv_info(int socfd,char* thepwd)		//接受文件函数
{
	int len;
	char buf[1000]={0};
	recv(socfd,&len,sizeof(len),0);
	recv(socfd,&buf,len,0);
	printf("the name is %s \n",buf);
	if(!strcmp(buf,"404"))
	{
		printf("服务器没有该文件！\n");
		return -1;
	}
	
	off_t f_size;
	recv_n(socfd,(char*)&len,sizeof(int));
	recv_n(socfd,(char*)&f_size,len);
	printf("the file size is %ld\n",f_size);
	float total=0;
	float j;
	struct timeval t,times,tt;
	gettimeofday(&t,NULL);
	gettimeofday(&times,NULL);
	
	int ffd;
	ffd=open(thepwd,O_RDWR|O_CREAT,0666);
	while(1)
	{
		recv_n(socfd,(char*)&len,sizeof(int));
		if(len==0)
		{
			printf("                        \r");
			printf("100%s","%");
			printf("\n");
			gettimeofday(&t,NULL);
			printf("本次下载用时%ld s %ld us\n",t.tv_sec-times.tv_sec,(long)abs(t.tv_usec-times.tv_usec));
		break;
		}
		
		total+=len;
		if(t.tv_usec>30000)
		{	
			printf("%5.2f%s\r",total/f_size*100,"%");
			fflush(stdout);
		}

		gettimeofday(&t,NULL);
		recv_n(socfd,buf,len);
		write(ffd,buf,len);
		bzero(buf,sizeof(buf));
	}
	printf("传输完成！\n");
	close(ffd);
}

int trans_info(int fd,char* FILENAME,char* thepwd)
{
	signal(SIGPIPE,SIG_IGN);

	train file;
	bzero(&file,sizeof(train));
	strcpy(file.buf,FILENAME);		//文件名拷贝到结构体中
	file.len=strlen(file.buf);		//文件名长度
	printf("the FILENAME is %s,len is %d\n",file.buf,file.len);
	send(fd,(char *)&file,4+file.len,0);	//发送文件名

	struct stat f_size;
	int ffd=open(thepwd,O_RDONLY);//打开文件，返回文件描述符
	if(ffd==-1)
	{
		perror("open");
		goto end;
	}
	fstat(ffd,&f_size);
	file.len=sizeof(off_t);
	memcpy(file.buf,&f_size.st_size,file.len);
	send_n(fd,(char*)&file,4+file.len);
	int ret;
	while((file.len=read(ffd,file.buf,sizeof(file.buf)))>0) //发送文件内容，直到为空
	{
		ret=send_n(fd,(char*)&file,4+file.len);
		if(ret==-1)
			goto end;
	}
	file.len=0;		//告诉客户端文件结束
	send_n(fd,(char *)&file,4);	//发送结束信息
	
	printf("传输完成！\n");

end:
	return 0;
}
