#include "work_que.h"

void que_init(pque_t pq,int capacity)
{
	pq->que_head=pq->que_tail=NULL;
	pq->que_capacity=capacity;
	pq->que_size=0;
	pthread_mutex_init(&pq->que_mutex,NULL);	//队列锁
}

void que_set(pque_t pq,pnode_t pnew)
{
	if(!pq->que_head)
	{
		pq->que_head=pnew;
		pq->que_tail=pnew;
	}else{
		pq->que_tail->nd_next=pnew;
		pq->que_tail=pnew;
	}
	pq->que_size++;
}

void que_get(pque_t pq,pnode_t* p)
{
	*p=pq->que_head;
	pq->que_head=pq->que_head->nd_next;
	pq->que_size--;
}

