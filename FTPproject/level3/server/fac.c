#include "factory.h"


void factory_init(pfac p,pfunc threadfunc,int cap)
{
	p->pthid=(pthread_t*)calloc(p->pthread_num,sizeof(pthread_t));	//分配线程ID数组
	pthread_cond_init(&p->cond,NULL);								//初始化条件变量
	que_init(&p->que,cap);											//队列初始化函数
	p->thread_func=threadfunc;										//指定线程函数
}


void factory_start(pfac p)
{
	int i;
	int t_id;
	if(!p->start_flag)			//避免重复创建线程
	{

		for(i=0;i<p->pthread_num;i++)
		{
			pthread_create(p->pthid+i,NULL,p->thread_func,p);
			printf("I am main_thread my id ,i create a  child, it's *p->pthid+i  is : %ld \n",*p->pthid+i);
		}
		p->start_flag=1;
	}
}

