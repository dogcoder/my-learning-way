#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void big(char *arr[],int size ,char** big1,char** big2){
	int i,j;
	char* temp;
	for(i=0;i<size;i++)
	printf("������ַ��� %d �� ��%s\n�䳤���� ��         %d\n\n",i+1,arr[i],strlen(*(arr+i)));

	for(i=0;i<size;i++){
		for(j=i+1;j<size;j++){
			if(strlen(*(arr+j))>strlen(*(arr+i))){
				temp=arr[j];
				arr[j]=arr[i];
				arr[i]=temp;
			}
		}
	}
	*big1=arr[0];
	*big2=arr[1];
}

int main(){
	char a[][10]={"12345","123456","99999999","7164299","4234"};
	char *p[5];
	char *big1,*big2;
	int i;
	for(i=0;i<5;i++){
		p[i]=a[i];
	}

	//big2=big1=&p[i];
	big(p,5,&big1,&big2);
	//big1=p;
	//big2=p+1;

	printf("���ֵΪ��%s \n�δ�ֵΪ��%s\n",big1,big2);


	system("pause");
}

