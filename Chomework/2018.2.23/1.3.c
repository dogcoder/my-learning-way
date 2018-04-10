#include <stdio.h>
#include <stdlib.h>

int mystrlen(char * a){
	int i;
	for(i=0;a[i]!='\0';i++);

	return i;
}

void mystrcat(char *a,char*b,int len)
{
	int i,lena,lenb;
	lena=mystrlen(a);
	lenb=mystrlen(b);

	if(len-1<(lena+lenb))
		printf("不能进行字符串拼接，空间不够！\n");

	for(i=0;i<(lena+lenb);i++)
		a[lena+i]=b[i];

	a[lena+i]=0;
}


int main(){
	char a[100];
	char b[30];
	int len=100;
	printf("请输入两个字符串 :\n");
	scanf("%s %s",a,b);

	mystrcat(a,b,len);

	printf("%s\n",a);

	system("pause");

}
