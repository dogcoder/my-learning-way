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
	off_t total=0;
	float j;
	struct timeval t,times,tt;
	gettimeofday(&t,NULL);
	gettimeofday(&times,NULL);

	int ffd;
	ffd=open(thepwd,O_RDWR|O_CREAT,0666);

	struct stat filesize;
	bzero(&filesize,sizeof(filesize));
	fstat(ffd,&filesize);
	printf("现在文件大小为:%ld\n",filesize.st_size);

	int N,lastnum;
	N=(f_size-filesize.st_size)/1000;		//1000字节接受次数
	lastnum=(f_size-filesize.st_size)%1000;	//最后一次接受字节数
	printf("lastnum = %d",lastnum);
	char bbuf[30]={0};
	sprintf(bbuf,"%ld",filesize.st_size);
	sendcomd1(bbuf,socfd);
	lseek(ffd,filesize.st_size,SEEK_SET);

	total+=filesize.st_size;

	if(f_size>(long)pow(2,27))
	{
		int i=0;
		int acc=0;
		printf("文件大于128M，接收到sendfile传输\n");
		int ret;
		for(i=1;i<N;i++)
		{
			ret=recv_n(socfd,buf,1000);
			write(ffd,buf,ret);
			total+=ret;
			if(t.tv_usec>30000)
			{	
				printf("%5.2f%s\r",(double)total/(double)f_size*100,"%");
				fflush(stdout);
			}
			gettimeofday(&t,NULL);
			bzero(buf,sizeof(buf));
		}
		recv_n(socfd,buf,lastnum);
		write(ffd,buf,lastnum);
		printf("传输完成\n");
		gettimeofday(&t,NULL);
		printf("\n本次下载用时%ld s %ld us\n",t.tv_sec-times.tv_sec,(long)abs(t.tv_usec-times.tv_usec));
		close(ffd);

	}else{
		int ret;
		printf("文件小于128M,普通传输\n");
		while(1)
		{
			ret=recv_n(socfd,(char*)&len,sizeof(int));
			if(len==0)
			{
				printf("\n");
				gettimeofday(&t,NULL);
				printf("本次下载用时%ld s %ld us\n",t.tv_sec-times.tv_sec,(long)abs(t.tv_usec-times.tv_usec));
				break;
			}

			total+=len;
			if(t.tv_usec>30000)
			{	
				//printf("%ld%s\r",total/f_size*100,"%");
				printf("%5.2f%s\r",(double)total/(double)f_size*100,"%");
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

	//断点续传
	off_t size;
	char bbuf[30]={0};
	recvcomd1(bbuf,fd);
	sscanf(bbuf,"%ld",&size);
	printf("服务端此时文件大小为：%ld\n",size);
	lseek(ffd,size,SEEK_SET);


	int ret;
	while((file.len=read(ffd,file.buf,sizeof(file.buf)))>0) //发送文件内容，直到为空
	{
		ret=send_n(fd,(char*)&file,4+file.len);
		if(ret==-1)
			goto end;
	}
	file.len=0;		//告诉服务器文件结束
	send_n(fd,(char *)&file,4);	//发送结束信息

	printf("传输完成！\n");

end:
	return 0;
}
