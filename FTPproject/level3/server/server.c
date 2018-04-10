#include "head.h"
#include "factory.h"
#include "work_que.h"
#include <sys/types.h>

void* thread_handle(void* p)
{
	char NowDir[30]={0};
	char USERNAME[50]={0};
	char AbsRoad[500]={0};
	int ret,ret1,ret2,ret3,ret4;
	ret1=ret2=ret3=ret4=0;
	int len1,len2;
	char comd[50],arg[500];
	pfac mp=(pfac)p;
	pque_t pq=&mp->que;
	pnode_t pcur;
	char thepwd[1024];
	getcwd(thepwd,sizeof(thepwd));
	sprintf(thepwd,"%s%s%s",thepwd,"/","user");	
	while(1)
	{
		pthread_mutex_lock(&pq->que_mutex);
		if(!pq->que_size)
		{
			pthread_cond_wait(&mp->cond,&pq->que_mutex);
		}
		que_get(pq,&pcur);
		pthread_mutex_unlock(&pq->que_mutex);
		printf("客户端连接成功！\n");

		ret=cli_land_confirm(pcur->nd_sockfd,USERNAME);	//客户端验证
		if(ret==-1)
		{
			printf("登陆失败\n");
			free(pcur);
			break;
		}
		sprintf(thepwd,"%s%s%s",thepwd,"/",USERNAME);	//用户登陆默认用户文件夹路径
		strcpy(NowDir,USERNAME);
		
		while(1)
		{
			bzero(&len1,4);
			bzero(&len2,4);
			bzero(comd,50);
			bzero(arg,50);
			ret1=recv_n(pcur->nd_sockfd,(char*)&len1,sizeof(len1));	//接受命令
			ret2=recv_n(pcur->nd_sockfd,comd,len1);
			ret3=recv_n(pcur->nd_sockfd,(char*)&len2,sizeof(len2));	//接受参数
			ret4=recv_n(pcur->nd_sockfd,arg,len2);
			if(ret1==-1||ret2==-1||ret3==-1||ret4==-1)
			{
				printf("客户端断开！\n");
				if(strlen(USERNAME)>0)
				user_O_F_line_record(" ","OFF");				//用户下线记录数据库
				break;
			}

			if(!strcmp(comd,"cd"))												//cd 命令处理单元
			{
				cd_comdfunc(arg,pcur->nd_sockfd,thepwd,USERNAME,NowDir);
				printf("NowDir is :%s\n",NowDir);
				msql_user_operation(USERNAME,"cd",arg);
			}else if(!strcmp(comd,"ls"))										//ls 命令处理单元
			{
				ls_comdfunc(pcur->nd_sockfd,thepwd);
				msql_user_operation(USERNAME,"ls"," ");
			}else if(!strcmp(comd,"pwd"))										//pwd 命令处理单元
			{
				train file;
				bzero(&file,sizeof(file));
				file.len=strlen(thepwd);
				strcpy(file.buf,thepwd);
				send_n(pcur->nd_sockfd,(char*)&file,4+file.len);
				msql_user_operation(USERNAME,"pwd"," ");
			}else if(!strcmp(comd,"gets"))										//文件传输（输出）
			{

				char file_path_name[1000];
				bzero(file_path_name,sizeof(file_path_name));
				sprintf(file_path_name,"%s%s%s",thepwd,"/",arg);
				int test=open(file_path_name,O_RDONLY);//打开文件，返回文件描述符
				if(test==-1)
				{
					train file;
					bzero(&file,sizeof(file));
					strcpy(file.buf,"404");		
					file.len=strlen(file.buf);
					send_n(pcur->nd_sockfd,(char*)&file,4+file.len);
					continue;
				}
				trans_info(pcur->nd_sockfd,arg,thepwd);
				msql_user_operation(USERNAME,"gets",arg);
			}else if(!strcmp(comd,"puts"))										//文件传输（接受）
			{
				//判断MD5存在与否
				unsigned char myMD5[35]={0};
				recvcomd1(myMD5,pcur->nd_sockfd);
				printf("myMD5 is :%s\n",myMD5);
				int ret=mysql_find_MD5(myMD5);		//验证是否存在MD5
				if(ret==-1)
				{
					printf("当前已存在该文件\n");
					sendcomd1("EXIST",pcur->nd_sockfd);
					//建立硬链接
					char oldroad[300]={0};
					char newroad[300]={0};
					sprintf(newroad,"%s/%s",thepwd,arg);
					mysql_find_AbsRoad(myMD5,oldroad);		//根据当前文件MD5码，寻找绝对路径用于硬链接
					link(oldroad,newroad);
					mysql_UserFile_insert(NowDir,arg,"---",myMD5,USERNAME,newroad); 
					continue;
				}
				sendcomd1("NONEEXIST",pcur->nd_sockfd);
				ret=recv_info(pcur->nd_sockfd,thepwd);
				if(ret==0){
					msql_user_operation(USERNAME,"puts",arg);
					sprintf(AbsRoad,"%s/%s",thepwd,arg);
					mysql_UserFile_insert(NowDir,arg,"---",myMD5,USERNAME,AbsRoad);		//用户文件录入
				}else if(ret==-1){
					msql_user_operation(USERNAME,"puts",arg);
					printf("本次下载未完成，不会录入UserFile");
				}
			}else if(!strcmp(comd,"remove"))									//文件删除
			{
				remove_file(thepwd,arg,pcur->nd_sockfd,USERNAME);
				msql_user_operation(USERNAME,"remove",arg);
			}else if(!strcmp(comd,"mkdir")){
				int ret=mkdir_comdfunc(pcur->nd_sockfd,arg,thepwd,NowDir,USERNAME);
				if(ret==-1)
					continue;
				msql_user_operation(USERNAME,"mkdir",arg);
			}else{																//错误命令反馈
				train file;
				bzero(&file,sizeof(file));
				strcpy(file.buf,"404");
				file.len=strlen(file.buf);
				send_n(pcur->nd_sockfd,(char*)&file,4+file.len);
			}
		}
		free(pcur);
	}
}

int main(int argc,char** argv)
{
	if(argc!=5)
	{
		printf("args error!\n");
		return -1;
	}

	fac myfac;
	bzero(&myfac,sizeof(fac));			//创建线程结构体
	int cap=atoi(argv[4]);				//队列容量
	int thread_num=atoi(argv[3]);		//线程数
	myfac.pthread_num=thread_num;
	factory_init(&myfac,thread_handle,cap);	//初始化
	factory_start(&myfac);					//创建线程

	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		return -1;
	}
	int reuse=1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&reuse,sizeof(int));
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));
	ser.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("bind");
		return -1;
	}
	listen(sfd,100);
	pnode_t pnew;
	int newfd;
	pque_t pq=&myfac.que;
	while(1)
	{
		newfd=accept(sfd,NULL,NULL);
		if(newfd==-1)
		{
			perror("accept");
			return -1;
		}
		pnew=(pnode_t)calloc(1,sizeof(node_t));
		pnew->nd_sockfd=newfd;
		pthread_mutex_lock(&pq->que_mutex);
		que_set(pq,pnew);
		pthread_mutex_unlock(&pq->que_mutex);
		pthread_cond_signal(&myfac.cond);
	}

	close(sfd);
	return 0;
}

