#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 100
int main(){
	char a[n];
	char *p=a;
	printf("��������ո��ַ������ַ�����ת��Ϊ%020 :");
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
