#include <stdio.h>
#include <stdlib.h>

#define N 10
void fun(int *a)
{
	int i,j,tmp=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N-i-1;j++)
			if(a[j]>a[j+1])
			{
				tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
			}

	}


}

int main()
{
	int i,a[N]={314,413,455,999,152,563,777,542,543,234};
	fun(a);

	printf("最大值为 %d, 次大值为 %d",a[N-1],a[N-2]);

	system("pause");


}
