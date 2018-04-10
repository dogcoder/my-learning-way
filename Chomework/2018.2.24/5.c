#include <stdio.h>
#include <stdlib.h>
#define N 100
void fun(char *pp)
{
	char *t,*p;
	for(p=pp;*p!='\0';p++){
	if(*p=='_'&&*(p+1)=='_')
	{
		for(t=p+1;*t!='\0';t++){
				*t=*(t+1);
			}
		p--;
	}
	}

	if(*pp=='_'){
		for(t=pp;*t!='\0';t++){
				*t=*(t+1);
			}
	}
	for(p=pp;*p!='\0';p++){
	if(*p=='_'&&*(p+1)=='\0'){
		for(t=p;*t!='\0';t++){
				*t=*(t+1);
			}
	}
	}

}

int main(){
	char a[N];

	gets(a);
	fun(a);
	printf("%s\n",a);

	system("pause");
}

