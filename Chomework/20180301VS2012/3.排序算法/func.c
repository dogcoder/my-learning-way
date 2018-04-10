#include "func.h"

void print(int *a)
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("%3d",a[i]);
	}
	printf("\n");
}

//ѡ������
void arr_select(int *a)
{
	int i,j,max_pos;
	for(i=N;i>1;i--)
	{
		max_pos=0;
		for(j=0;j<i;j++)
		{
			if(a[max_pos]<a[j])
			{
				max_pos=j;
			}
		}
		SWAP(a[max_pos],a[j-1]);
	}
}
//��������
void arr_insert(int *a)
{
	int i,j,k,insert_val;
	for(i=1;i<N;i++)//Ҫ�������������
	{
		insert_val=a[i];
		for(j=0;j<i;j++)//����������Ŀ
		{
			if(a[i]<a[j])
			{
				for(k=i-1;k>=j;k--)//�����ƶ�
				{
					a[k+1]=a[k];
				}
				break;
			}
		}
		a[j]=insert_val;
	}
}

int partition(int *a,int left,int right)
{
	int i,k=left;
	for(i=left;i<right;i++)
	{
		if(a[i]<a[right])
		{
			SWAP(a[i],a[k]);
			k++;
		}
	}
	SWAP(a[k],a[right]);
	return k;
}
//����
void arr_quick(int *a,int left,int right)
{
	int pivot;
	if(left<right)
	{
		pivot=partition(a,left,right);
		arr_quick(a,left,pivot-1);
		arr_quick(a,pivot+1,right);
	}
}

void heap_max(int *a,int i,int size)
{
	int dad,son;
	dad=i;
	son=2*dad+1;
	while(son<size)
	{
		if(son+1<size&&a[son]<a[son+1])
		{
			son++;
		}
		if(a[dad]<a[son])
		{
			SWAP(a[dad],a[son]);
			dad=son;
			son=2*dad+1;
		}else{
			break;
		}
	}
}

void arr_heap(int *a)
{
	int i=0;
	for(i=N/2-1;i>=0;i--)//�����Ϊ�󶥶�
	{
		heap_max(a,i,N);
	}
	SWAP(a[0],a[N-1]);//�Ѷ���Ԫ�طŵ����
	for(i=N-1;i>0;i--)
	{
		heap_max(a,0,i);//ֻ�ж���������󶥶ѣ����е���
		SWAP(a[0],a[i-1]);
	}
}

int compare(const void *left, const void *right) 
{
	int *p0=(int*)left;
	int *p1=(int*)right;
	if(*p0>*p1)
	{
		return 1;
	}else if(*p0==*p1)
	{
		return 0;
	}else{
		return -1;
	}
}