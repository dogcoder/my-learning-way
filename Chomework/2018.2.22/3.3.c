#include <stdio.h>
#include <stdlib.h>


int main(){
	
	long x,ten;
	int i;
	char a[30];

	while(scanf("%ld",&ten)!=EOF){
		printf("你输入的十进制为：      %ld\n",ten);
		for(i=0;i<30&&ten>0;i++){
			x=ten%16;
			ten/=16;
			switch(x){
			case 0: a[i]='0';break;
				case 1: a[i]='1';break;
					case 2: a[i]='2';break;
						case 3: a[i]='3';break;
			case 4: a[i]='4';break;
				case 5: a[i]='5';break;
					case 6: a[i]='6';break;
						case 7: a[i]='7';break;
			case 8: a[i]='8';break;
				case 9: a[i]='9';break;
					case 10: a[i]='A';break;
						case 11: a[i]='B';break;
			case 12: a[i]='C';break;
				case 13: a[i]='D';break;
					case 14: a[i]='E';break;
						case 15: a[i]='F';break;
			}

		}
		printf("\n");

		printf("转为为十六进制显示为：0X");
		for(;i>0;i--)
			printf("%c",a[i-1]);

		printf("\n");


	}

	system("pause");
}
