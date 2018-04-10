#include <stdio.h>
#include <stdlib.h>

void fun(void)
{
	int i,j,k;

	for(i=0;i<4;i++)
	{
		for(j=0;j<=5+i;j++)
			if(j==5+i||j==(5+i)-2*i)
				printf("*");
			else 
				printf(" ");
		printf("\n");
	}

	for(i=4;i>=0;i--)
	{
		for(j=0;j<=5+i;j++)
			if(j==5+i||j==(5+i)-2*i)
				printf("*");
			else 
				printf(" ");
		printf("\n");
	}
	
	

}

int main()
{
	fun();

	system("pause");
}