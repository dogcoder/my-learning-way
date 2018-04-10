#include <stdio.h>
#include <stdlib.h>


int main(){
	int y,m,d,i=1,days=0;

	for( ;scanf("%d%d%d",&y,&m,&d)!=EOF;days=0,i=1){
	while(i<m){
		switch(i){
		case 2:days+=28+(y%4==0&&y%100!=0||y%400==0);i++;continue;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:days+=31;i++;continue;

		case 4:
		case 6:
		case 9:
		case 11:days+=30;i++;continue;	
		}
	}
	days+=d;
	printf("今天是今年的第%d天!\n",days);
	
	}
	system("pause");
}
