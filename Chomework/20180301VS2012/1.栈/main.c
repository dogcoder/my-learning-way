#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tag{
	int val;
	struct tag *pNext;
}Node,*pNode;

typedef struct{
	pNode phead;
	int size;//栈中的元素个数
}Stack,*pStack;

//栈是先进后出

void push(pStack p,int val)
{
	pNode pnew=(pNode)calloc(1,sizeof(Node));
	pnew->val=val;
	if(NULL==p->phead)
	{
		p->phead=pnew;
	}else{
		pnew->pNext=p->phead;
		p->phead=pnew;
	}
	p->size++;
}
void pop(pStack p)
{
	pNode pcur;
	if(NULL==p->phead)
	{
		printf("stack is empty\n");
		return;
	}
	pcur=p->phead;
	p->phead=pcur->pNext;
	p->size--;
	free(pcur);
	pcur=NULL;
}
int size(pStack p)
{
	return p->size;
}
int main()
{
	Stack s;
	int i,s_size;
	memset(&s,0,sizeof(s));
	while(scanf("%d",&i)!=EOF)
	{
		push(&s,i);
	}
	pop(&s);
	s_size=size(&s);
	printf("s_size=%d\n",s_size);
	system("pause");
}