#include <stdio.h>
#include <stdlib.h>
#define len(x)	sizeof(x)/sizeof(x[0])

int getfirstbit(int num)
{
	return num & ~(num-1);
}

void funtwo(int *a,int llen)
{
	int i,aORb=0,listbit,aa=0,b=0;
 

	for(i=0;i<llen;i++)
		aORb^=a[i];
	listbit=getfirstbit(aORb);

	for(i=0;i<llen;i++)
		if(a[i]&listbit)
			aa^=a[i];
	b=aa^aORb;
	printf("\n第二个数为 %d\n 第三个数为%d\n",aa,b);
}

int funthree(int *a,int llen){
	int i,aorborc=0,firstbit=0,d=0;

	for(i=0;i<llen;i++)
		aorborc^=a[i];
	printf("aorborc= %d\n",aorborc);

	for(i=0;i<llen;i++)
		firstbit^=getfirstbit(aorborc^a[i]);

	for(i=0;i<llen;i++){
		if(getfirstbit(a[i]^aorborc)&firstbit){
			d^=a[i];	
		}
	}
	printf("第一个数为%d",d);
		return d;
}

int main()
{
	int a[19]={16,2,3,4,5,6,7,8,14,15,1,8,7,6,5,4,3,2,16};
	int i;
	int a2[20]={16,2,3,4,5,6,7,8,14,15,1,8,7,6,5,4,3,2,16,0};
	i=funthree(a,19); 
	a2[19]=i;
	funtwo(a2,20);
	system("pause");
}
