#include <stdio.h>
#include <stdlib.h>

int mystrlen(char * a){
	int i;
	for(i=0;a[i]!='\0';i++);

	return i;
}


int mystrcmp(char* a,char* b){
	int i,x=5,len,lena,lenb;
	
	lena=mystrlen(a);
	lenb=mystrlen(b);
	if(lena>=lenb)
		len=lenb;
	else
		len=lena;
	

	for(i=0;i<len;i++){
		if(a[i]==b[i])
			x=0;
		else if(a[i]<b[i]){
			x=-1; break;
		}else if(a[i]>b[i]){
			x=1; break;
		}
}
	
	return x;
}


int main(){
	char a[100];
	char b[100];
	int x;
	printf("ÇëÊäÈëÁ½¸ö×Ö·û´® :");
	scanf("%s %s",&a,&b);
	//printf("\n");
	x=mystrcmp(a,b);

	printf("x=%d\n",x);

	system("pause");
}
