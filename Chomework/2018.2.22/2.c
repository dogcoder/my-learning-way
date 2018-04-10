#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100


void fun(int a,int n,int o)
{
			printf(" %d       %d       %d \n",a,n,o);
	while(a>0||n>0||o>0)
	{
		if(a>0&&n>0&&o>0)
			printf("*****  *****  *****\n");
		else if(a>0&&n>0&&o<=0)
			printf("*****  *****       \n");
		else if(a>0&&n<=0&&o>0)
			printf("*****         *****\n");
		else if(a>0&&n>0&&o<=0)
			printf("       *****  *****\n");
		else if(a>0&&n<=0&&o<=0)
			printf("*****              \n");
		else if(a<=0&&n>0&&o<=0)
			printf("       *****       \n");
		else if(a<=0&&n<=0&&o>0)
			printf("              *****\n");

		a--;
		n--;
		o--;
	}
			printf(" alp    num     oth\n");
	
}


int main()
{
	int len,i,alp=0,num=0,oth=0;

	char a[N];
	
	scanf("%s",a);
	len=strlen(a);

	for(i=0;i<len;i++)
	{
		if(a[i]>='a'&&a[i]<='z'||a[i]>='A'&&a[i]<='Z'){
			alp++;
		}else if(a[i]>='0'&&a[i]<='9'){
			num++;
		}
	 else  oth++;

	}



	fun(alp,num,oth);
	system("pause");
}
