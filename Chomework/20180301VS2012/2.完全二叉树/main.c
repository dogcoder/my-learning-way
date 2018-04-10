#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char c;
	struct node *pleft;
	struct node *pright;
}Node,*pNode;

typedef struct width{
	pNode now;
	struct width *pNext;
}Width,*pWidth;

void preOrder(pNode p)
{
	if(p)
	{
		putchar(p->c);
		preOrder(p->pleft);
		preOrder(p->pright);
	}
}

void midOrder(pNode p)
{
	if(p)
	{
		midOrder(p->pleft);
		putchar(p->c);
		midOrder(p->pright);
	}
}

void latOrder(pNode p)
{
	if(p)
	{
		latOrder(p->pleft);
		latOrder(p->pright);
		putchar(p->c);
	}
}
#define N 10
//�����ƽ�����Ԫ�أ��ڲ�ѭ����æ�ҵ����е�λ��
void buildtree(pNode *tree2,char* c)
{
	pNode tree=NULL,pnew;
	pWidth phead=NULL,ptail=NULL,lpnew,lpcur;//��β�巨�½�����
	int i=0;
	while(c[i])
	{
		pnew=(pNode)calloc(1,sizeof(Node));
		pnew->c=c[i];
		lpnew=(pWidth)calloc(1,sizeof(Width));//������ȱ���
		lpnew->now=pnew;
		if(NULL==tree)
		{
			tree=pnew;
			i++;
			phead=lpnew;//����β�巨��������Ϊ��ʱ
			ptail=lpnew;
			lpcur=phead;
			continue;
		}
		ptail->pNext=lpnew;//����Ϊ�գ�������
		ptail=lpnew;
		while(lpcur)//ÿ�δ�����ͷ��λ��
		{
			if(NULL==lpcur->now->pleft)
			{
				lpcur->now->pleft=pnew;
				break;
			}else if(NULL==lpcur->now->pright)
			{
				lpcur->now->pright=pnew;
				break;
			}
			lpcur=lpcur->pNext;
		}
		i++;
	}
	*tree2=tree;
}

int main()
{
	char c[N+1]="ABCDEFGHIJ";
	pNode p[N];
	int i,j;
	pNode tree=NULL;
	//for(i=0;i<N;i++)//��ÿһ���ڵ�ռ�����ã�ͬʱ��ֵ
	//{
	//	p[i]=(pNode)calloc(1,sizeof(Node));
	//	p[i]->c=c[i];
	//}
	//for(i=0;i<N;i++)//�����ƽ�����Ԫ��
	//{
	//	if(NULL==tree)
	//	{
	//		tree=p[i];
	//		continue;
	//	}
	//	for(j=0;j<N;j++)//�ڲ�ѭ����æ�ҵ����е�λ��
	//	{
	//		if(NULL==p[j]->pleft)
	//		{
	//			p[j]->pleft=p[i];
	//			break;
	//		}else if(NULL==p[j]->pright)
	//		{
	//			p[j]->pright=p[i];
	//			break;
	//		}
	//	}
	//}
	buildtree(&tree,c);
	preOrder(tree);
	printf("\n");
	midOrder(tree);
	printf("\n");
	latOrder(tree);
	printf("\n");
	system("pause");
}