#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "head.h"
#include "work_que.h"

typedef void* (*pfunc)(void*);

typedef struct{
	pthread_t *pthid;			//存储线程ID
	pthread_cond_t cond;		//条件变量
	que_t que;					//队列信息结构体
	int pthread_num;			//线程数量
	int start_flag;				//线程启动标志
	pfunc thread_func;			//线程处理函数
}fac,*pfac;

typedef struct{
	int len;					//传送字节数
	char buf[1000];
}train;


void factory_init(pfac,pfunc,int);	//工厂初始化

void factory_start(pfac);			//创建线程

int send_n(int fd,char* file,int len);	//发送（单次）

int recv_n(int fd, char*file,int len);	//接受

int trans_info(int fd,char* FILENAME,char* thepwd);			//传输文件（一次传输任务）

int recv_info(int socfd,char* thepwd);		//接受文件函数

int remove_file(char*,char*,int socfd,char* Username);		//删除文件

#endif
