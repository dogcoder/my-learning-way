#include <stdio.h>
#include <stdlib.h>
#define N 100

void fun(char *a)					
{
	char* p;
	char* t;
	char* pt;
	char b;
	int count=0;
	for(pt=a;*pt!='\0';pt++){
		b=*pt;
	for(p=pt+1;*p!='\0';p++)	{
		if(*p==b){
			for(t=p;*t!='\0';t++){
				*t=*(t+1);
				count++;
			}		
			p--;
		}
	}
	}

	printf("count = %d\n",count);
}


int main(){
	char a[N];
	int i=0;
	printf("请输入一个字符串，函数将减去字符串中相同字符！\n");
	scanf("%s",a);
	fun(a);

	printf("%s",a);
	
	system("pause");

}
