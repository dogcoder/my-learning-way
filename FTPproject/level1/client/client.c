#include "head.h"

void sendcomd(char*,char*,int socfd);

int main(int argc,char **argv)
{	
	if(argc!=3)
	{
		printf("args error");
		return -1;
	}

	int socfd=socket(AF_INET,SOCK_STREAM,0);
	if(socfd==-1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in cli;
	bzero(&cli,sizeof(cli));
	cli.sin_family=AF_INET;
	cli.sin_addr.s_addr=inet_addr(argv[1]);
	cli.sin_port=htons(atoi(argv[2]));

	int ret=connect(socfd,(struct sockaddr*)&cli,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("connect");
		return -1;
	}
	printf("connect successful!\n");

	char comd[50],arg[50];			//客户端输入命令及命令参数
	int len;
	char buf[1000];

	char thepwd[1000];
	bzero(thepwd,sizeof(thepwd));
	getcwd(thepwd,sizeof(thepwd));
	sprintf(thepwd,"%s%s%s",thepwd,"/","myfile");


	while(1)
	{
		fflush(stdin);
		bzero(comd,sizeof(comd));
		bzero(arg,sizeof(arg));
		printf("请输入命令、参数（空格隔开）：\n");

		char buf_in[1000]={0};
		bzero(buf_in,1000);
		fgets(buf_in,1000,stdin);
		sscanf(buf_in,"%s %s",comd,arg);
		fflush(stdin);


		char file_pathe_name[1000];
		bzero(file_pathe_name,sizeof(file_pathe_name));
		sprintf(file_pathe_name,"%s%s%s",thepwd,"/",arg);

		if(!strcmp(comd,"puts"))			//执行上传命令前检测文件是否存在
		{
			int test=open(file_pathe_name,O_RDONLY);
			if(test==-1)
			{
				printf("该文件不存在！\n");
				sleep(3);
				continue;
			}
		}

		sendcomd(comd,arg,socfd);

		if(!strcmp(comd,"cd")||!strcmp(comd,"ls")||!strcmp(comd,"remove"))		//进入cd ls remove单元
		{

			system("clear");
			bzero(buf,sizeof(buf));
			recv_n(socfd,(char*)&len,sizeof(len));
			recv_n(socfd,buf,len);
			printf("%s\n",buf);
			bzero(buf,1000);
		}else if(!strcmp(comd,"pwd"))											//显示当前路径
		{

			system("clear");
			bzero(buf,sizeof(buf));
			recv_n(socfd,(char*)&len,sizeof(len));
			recv_n(socfd,buf,len);
			printf("当前路径为：%s\n",buf);
			bzero(buf,1000);
		}else if(!strcmp(comd,"gets"))											//进入接受文件处理单元
		{
			int test=recv_info(socfd,file_pathe_name);
			if(test==-1)
				sleep(2);
		}else if(!strcmp(comd,"puts"))											//进入发送文件处理单元
		{
			trans_info(socfd,arg,file_pathe_name);	
		}else{																	//进入错误命令处理单元
			system("clear");
			recv_n(socfd,(char*)&len,sizeof(len));
			recv_n(socfd,buf,len);
			if(!strcmp(buf,"404"))
			{
				printf("服务器反馈：指令非法！\n");
				continue;
			}
		}
	}
	printf("now I will leave the server!\n");
	close(socfd);
	return -1;
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
