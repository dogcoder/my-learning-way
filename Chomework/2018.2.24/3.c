#include <stdio.h>
#include <stdlib.h>
#define N 100

void fun(char *a,char b)
{
	char* p;
	char* t;
	for(p=a;*p!='\0';p++)	{
		if(*p==b){
			for(t=p;*t!='\0';t++){
				*t=*(t+1);
			}		
			p--;
		}
	}
}


int main(){
	char a[N];
	char b;
	int i=0;
	printf("������һ���ַ�����һ���ַ�����������ȥ�ַ����и��ַ���\n");
	scanf("%s",a);
	getchar();
	scanf("%c",&b);
	fun(a,b);

	printf("%s",a);
	
	system("pause");

}
