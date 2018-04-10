#include <stdio.h>
#include <stdlib.h>

#define n 100

int mystrlen(char * a){
	int i;
	for(i=0;a[i]!='\0';i++);

	return i;
}

int main(){

	char a[n]={0,};
	int i,len,x=0,count=0;
	gets(a);
	len=mystrlen(a);
	for(i=0;i<len;i++){
		if(a[i]==' '&&x==0)
			 ;
		else if(a[i]!=' '&&x==0){
			x=1;
			count++;
		}else if(a[i]!=' '&&x==1)
			 ;
		else if(a[i]==' '&&x==1){
			x=0;
			
		}
	}
	//printf("input: %s\n",a);
	//printf("count= %d\n",count);
	//printf("len=%d\n",len);
	for(i=0;i<len;i++){
		if(a[i]==' '){
			continue;
		}
			printf("%c",a[i]);
		if(a[i]!=' '&&a[i+1]==' '&&count!=0){
			printf("\n");
			count--;
		}
	}
	printf("\n");
	system("pause");

}
