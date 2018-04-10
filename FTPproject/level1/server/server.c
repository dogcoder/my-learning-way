#include "head.h"
#include "factory.h"
#include "work_que.h"
#include <sys/types.h>

pthread_mutex_t mutex;
void* thread_handle(void* p)
{
	int ret,ret1,ret2,ret3,ret4;
	ret1=ret2=ret3=ret4=0;
	int len1,len2;
	char comd[50],arg[50];
	pfac mp=(pfac)p;
	pque_t pq=&mp->que;
	pnode_t pcur;
	char thepwd[1024];
	getcwd(thepwd,sizeof(thepwd));
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
				break;
			}

			if(!strcmp(comd,"cd"))												//cd 命令处理单元
			{
				cd_comdfunc(arg,pcur->nd_sockfd,thepwd);
			}else if(!strcmp(comd,"ls"))										//ls 命令处理单元
			{
				pthread_mutex_lock(&mutex);
				ls_comdfunc(pcur->nd_sockfd,thepwd);
				pthread_mutex_unlock(&mutex);
			}else if(!strcmp(comd,"pwd"))										//pwd 命令处理单元
			{
				train file;
				bzero(&file,sizeof(file));
				file.len=strlen(thepwd);
				strcpy(file.buf,thepwd);
				send_n(pcur->nd_sockfd,(char*)&file,4+file.len);
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
			}else if(!strcmp(comd,"puts"))										//文件传输（接受）
			{
				recv_info(pcur->nd_sockfd,thepwd);
			}else if(!strcmp(comd,"remove"))									//文件删除
			{
				remove_file(thepwd,arg,pcur->nd_sockfd);
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
	pthread_mutex_init(&mutex,NULL);
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

