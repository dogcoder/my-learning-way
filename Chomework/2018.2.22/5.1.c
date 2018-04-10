#include <stdio.h>
#include <stdlib.h>


int main(){
	int i,a[7]={1,2,3,4,4,2,1};
	int len,thenumber=0;
	for(i=0;i<7;i++)
		thenumber^=a[i];

	printf("不同的值为 : %d ",thenumber);

	system("pause");
}
