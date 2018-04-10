#include <stdio.h>
#include <stdlib.h>

void fun(int *a,int *b,int *c,int *d)
{
	int i,j,k;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i]==b[j])
			{
				for(k=0;k<10;k++)
					if(a[i]==c[k])
						*d++=a[i];
			}

				
		}

	}

}



int main()
{
	int a[10]={1,2,3,4,5,6,7,8,9,10};
	int b[10]={6,7,8,9,10,11,12,13,14,15};
	int c[10]={9,10,11,12,13,14,15,16,17,18};
	int d[5]={0,};
	int i;
	fun(a,b,c,d);

	for(i=0;d[i]!=0;i++)
		printf(" d[%d] = %d\n",i,d[i]);

	system("pause");
}