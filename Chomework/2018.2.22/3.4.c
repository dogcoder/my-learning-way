#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define sixteen 16
int main(){
	char a[30];
	long long x=0,sum=0;
	int i=0;
	int len;

	printf("������ʮ���������� 0X");
	while(fflush(stdin),scanf("%s",a)!=EOF){
		for(i=0;i<strlen(a);){
		
		switch(a[i]){
		case '0': x=0;i++;sum=sum*16+x;continue;
		case '1': x=1;i++;sum=sum*16+x;continue;
		case '2': x=2;i++;sum=sum*16+x;continue;
		case '3': x=3;i++;sum=sum*16+x;continue;

		case '4': x=4;i++;sum=sum*16+x;continue;
		case '5': x=5;i++;sum=sum*16+x;continue;
		case '6': x=6;i++;sum=sum*16+x;continue;
		case '7': x=7;i++;sum=sum*16+x;continue;

		case '8': x=8;i++;sum=sum*16+x;continue;
		case '9': x=9;i++;sum=sum*16+x;continue;
		case 'A': x=10;i++;sum=sum*16+x;continue;
		case 'B': x=11;i++;sum=sum*16+x;continue;

		case 'C': x=12;i++;sum=sum*16+x;continue;
		case 'D': x=13;i++;sum=sum*16+x;continue;
		case 'E': x=14;i++;sum=sum*16+x;continue;
		case 'F': x=15;i++;sum=sum*16+x;continue;
		}
		
	
	}
		printf("��������ǣ�%s   len=%d    i=%d \n",a,strlen(a),i);
		printf("ʮ������ת��Ϊʮ����Ϊ��%lld\n",sum);
		sum=0;
		printf("������ʮ���������� 0X");
	}

	

	system("pause");
}
