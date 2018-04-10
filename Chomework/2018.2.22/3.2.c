#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){

	char a[100];
	int len,i;
	long x=0;
	while(scanf("%s",a)!=EOF){
		if(strlen(a)>100)
			printf("the number is too big to transferm!\n ");
		len=strlen(a);
		//printf("len = %d\n",len);
		for(i=len;i>0;i--)
			x+=(a[i-1]-48)*((int)pow(2.0,len-i));
		printf("x = %ld\n",x);
		x=0;
		len=0;
	}

	system("pause");
}
