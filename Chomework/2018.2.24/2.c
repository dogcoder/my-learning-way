#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 100
int main(){
	char a[n];
	char *p=a;
	printf("请输入带空格字符串，字符串将转化为%020 :");
	gets(a);
	for(;*p!='\0';p++){
		if(*p==' ')
			printf("%%020");
		else
			printf("%c",*p);
	}
	printf("\n");
	system("pause");
}
