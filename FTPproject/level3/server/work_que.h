#ifndef _WORK_QUE_H__
#define _WORK_QUE_H__
#include "head.h"

typedef struct tag_node{
	int nd_sockfd;
	struct tag_node* nd_next;
}node_t,*pnode_t;	//元素结构体，存储实际client fd;

typedef struct tag_que{
	pnode_t que_head,que_tail;
	int que_capacity;
	int que_size;

	pthread_mutex_t que_mutex;
}que_t,*pque_t;		//描述队列的结构体

void que_init(pque_t pq,int capacity);		//队列初始化

void que_set(pque_t pq,pnode_t pnew);		//将任务（客户端socket）放置队列中

void que_get(pque_t pq,pnode_t* p);			//从队列中取任务（描述符）
#endif

