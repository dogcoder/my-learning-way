#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fun(int y,int m,int d){
	int i=1,days=0;

	while(i<m){
		switch(i){
		case 2:
			if(y%4==0&&y%100!=0||y%400==0){
				days+=29;i++;}
			else{
				days+=28;i++;}continue;
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
	return days;
}
int main(){
	int y1,m1,d1,nn;
	int y2=2018,m2=1,d2=7;//基准日，该日为星期日
	int days1=0,days2=0,n,sum=0;

	printf("请输入一个日期，将计算出是星期几：\n");
	scanf("%d%d%d",&y1,&m1,&d1);
	printf("%d-%d-%d\n",y1,m1,d1);

	days1=fun(y1,m1,d1);
	days2=fun(y2,m2,d2);
	if(y1>y2||y1==y2&&m1>m2||y1==y2&&m1==m2&&d1>d2){
		n=y2;
		nn=y1;
	}else{
		nn=y2;	
		n=y1;
	}
	for(n;n<nn;n++)
	{
		sum+=fun(n,12,31);
	}
	//printf("%d\n",sum);
	sum=abs(sum-days1+days2);
	//printf("%d\n",sum);

	if(y1>=y2)
		sum%=7;
	else
		sum=(7-sum%7)%7;

	switch(sum){
	case 0:printf("今天是星期天 ！\n");break;
		case 1:printf("今天是星期一 ！\n");break;
			case 2:printf("今天是星期二 ！\n");break;
				case 3:printf("今天是星期三 ！\n");break;
					case 4:printf("今天是星期四 ！\n");break;
						case 5:printf("今天是星期五 ！\n");break;
							case 6:printf("今天是星期六 ！\n");break;
	}

	system("pause");
}
