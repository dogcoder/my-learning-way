#include <stdio.h>
#include <stdlib.h>

#define n 8
int fun(int *a)
{
	int i,j,min=666;

	for(i=0;i<n;i++)
	{
		for(j=1+i;j<n;j++)
			if(abs(a[i]-a[j])<min)
				min=abs(a[i]-a[j]);
	}
	return min;
}


int main()
{
	int  a[n]={6,555,156,204,245,320,354,8};
 

	printf("min = %d",fun(a));

	system("pause");

}
