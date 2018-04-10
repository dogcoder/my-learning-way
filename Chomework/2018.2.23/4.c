#include <stdio.h>
#include <stdlib.h>
#define no -1
int mystrlen(char * a){
	int i;
	for(i=0;a[i]!='\0';i++);
	if(i==0)
		return i;
	else 
		return i-1;
}

void reverse(char *a,int len){
	int i=0;
	char temp;
	for(i=0;i<len;i++,len--){
		temp=a[i];
		a[i]=a[len];
		a[len]=temp;
	}
	
 
}


int main(){
	char temp,a[100];
	int i,j,k,len,x=no;
	
	gets(a);
	printf("INPUT IS   : %s\n",a);
	len=mystrlen(a);
	printf("lenth = %d\n",len);
	reverse(a,len);
	printf("REVERSE IS : %s\n",a);
	for(i=0;i<len;i++){
		 if(a[i]==' '&&x==no||a[i]!=' '&&x!=no)
			 continue;
		 else if(a[i]!=' '&&x==no){
					x=i;
		 }else if(a[i]==' '&&x!=no){
				j=i-1;
				for(x;x<j;x++,j--){
				 temp=a[x];
				 a[x]=a[j];
				 a[j]=temp;
			 }
			 x=no;
		 }
	}
	if(i==len&&x!=no){
		j=i;
		for(x;x<j;x++,j--){
			temp=a[x];
			a[x]=a[j];
			a[j]=temp;
		}
	}
	printf("REVERSE IS : %s\n",a);

	system("pause");
}
