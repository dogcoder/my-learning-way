#include <stdio.h>
#include <stdlib.h>


int mystrlen(char * a){
	int i;
	for(i=0;a[i]!='\0';i++);

	return i;
}


int mystrcpy(char *a,char *b){
	int i,lena,lenb;
	lena=100;
	lenb=mystrlen(b);

	if(lena<lenb)
		return -1;
	
	for(i=0;i<lenb;i++)
		a[i]=b[i];

	a[i]=0;
	return 0;
}

int main()
{
	char a[100]={0,};
	char b[]="hello my friend!";
	int aa;

	aa=mystrcpy(a,b);

	if(aa==0)
		printf("%s\n",a);
	else
		printf("wrong input");

	system("pause");

}



