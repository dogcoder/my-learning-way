#include <stdio.h>
#include <stdlib.h>
#define n 1001
int fun(int *a)
{
	int i,j,same,x,y;
	for(i=0;i<n;i++)
	{
		for(j=1+i;j<n;j++)
			if(a[i]==a[j])
			{
				same=a[i];
				x=i;
				y=j;
				printf("a[%d] = a[%d] \n",x,y);
			}
	}
	return same;
}

int main(){
	int a[n],i;

	
	for(i=0;i<n;i++)
		a[i]=i;
	a[45]=9979;
	a[789]=9979;
	
	printf("%d",fun(a));

	system("pause");
}

