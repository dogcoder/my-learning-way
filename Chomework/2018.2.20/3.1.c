#include <stdio.h>
#include <stdlib.h>

void fun(int *a,int *b,int *c)
{
	int i,j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i]==b[j])
				*c++=a[i];
		}

	}

}



int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int b[10]={6,7,8,9,10,11,12,13,14,15};
	int c[10]={0,0,};
	int i;
	fun(a,b,c);

	for(i=0;c[i]!=0;i++)
		printf(" c[%d] = %d\n",i,c[i]);

	system("pause");
}
