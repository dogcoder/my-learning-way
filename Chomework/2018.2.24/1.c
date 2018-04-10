#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
int main(){
	int i,j,count=0;
	char temp;
	char a[N];
	scanf("请输入包含数字和字母的字符串： ");
	gets(a);

	if ((int)strlen(a)>N)
		printf("WRONG,INPUT IS TOO BIG!\n");

	printf("输入是:%s\n",a);
	for(i=0;i<(int)strlen(a);i++){
		if(a[i]>='0'&&a[i]<='9'){
			for(j=i;j>count;j--){
				temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
			count++;
		}else
			continue;
	}

	printf("结果是:%s\n",a);
	system("pause");
}
