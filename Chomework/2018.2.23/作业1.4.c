#include <stdio.h>
#include <stdlib.h>

int mystrlen(char * a){
	int i;
	for(i=0;a[i]!='\0';i++);

	return i;
}

int main(){
	int len;
	char a[100];
	while(fflush(stdin),gets(a)){
	len=mystrlen(a);
	printf("%d\n",len);
	
	}
	system("pause");
}

