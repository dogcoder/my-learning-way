#include <stdio.h>
#include <stdlib.h>
#define N 8

int fun(int *a)
{
	int b,i,j,count=0;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(a[i]==a[j])
			{
				count++;
			}
		}
		if(count>=4)
		{
		b=a[i];
		count=0;
		}

	}
	return b;
}

int main()
{
	int a[N]={1,1,1,1,1,2,3,4},b;
	b=fun(a);

	printf("b=%d",b);

	system("pause");

}

