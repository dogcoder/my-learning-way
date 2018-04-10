#include <stdio.h>
#include <stdlib.h>

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
	int y1,m1,d1;
	int y2,m2,d2;
	int days1=0,days2=0,n,sum=0;
nnnnn:
	printf("请输入两个日期，求其天数之差：\n");
	printf("第一个日期：");
	scanf("%d%d%d",&y1,&m1,&d1);
	printf("%d-%d-%d\n",y1,m1,d1);
	printf("第二个日期：");
	scanf("%d%d%d",&y2,&m2,&d2);
	printf("%d-%d-%d\n",y2,m2,d2);

	if(y2<=y1&&m2<=m1&&d2<d1){
		printf("ERROR,the first date must smaller than the second!\n");
		goto nnnnn;
	}
	days1=fun(y1,m1,d1);
	days2=fun(y2,m2,d2);

	for(n=y1;n<y2;n++)
	{
		sum+=fun(n,12,31);
	}
	sum=sum-days1+days2;
	printf("%d-%d-%d  距离 %d-%d-%d 有 %d 天\n",y2,m2,d2,y1,m2,d2,sum);
	system("pause");
}
