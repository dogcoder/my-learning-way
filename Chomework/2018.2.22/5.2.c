#include <stdio.h>
#include <stdlib.h>
#define len(x)	sizeof(x)/sizeof(x[0])

int getfirstbit(int num)
{
	return num & ~(num-1);
}

void fun(int *a,int *b,int llen)
{
	int i,aORb=0,listbit;
 

	for(i=0;i<llen;i++)
		aORb^=a[i];
	listbit=getfirstbit(aORb);

	for(i=0;i<llen;i++)
		if(a[i]&listbit)
			b[0]^=a[i];
	b[1]=b[0]^aORb;
	printf("%d\n",llen);
}


int main()
{
	int a[18]={1,2,3,4,5,6,7,13,10,10,8,7,6,5,4,3,2,1};
	int b[2]={0,0};
	int llen=len(a);
	fun(a,b,llen);
	printf("第一个数为 %d  \n第二个数为 %d",b[0],b[1]);
	system("pause");
}
