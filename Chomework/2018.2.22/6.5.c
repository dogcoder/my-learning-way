#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fun(int y,int m,int d){           //����������ǵ���ڶ�����


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

int what_week(int y1,int y2,int m1,int m2,int d1,int d2,int days1,int days2)  //������µڼ���Ϊ���ڼ�
{                                                                           

	int n,nn,sum=0;				
	if(y1>y2||y1==y2&&m1>m2||y1==y2&&m1==m2&&d1>d2){           //ȷ����������Ϊ��׼����ǰ���ߺ�
		n=y2;
		nn=y1;
	}else{
		nn=y2;	
		n=y1;
	}
	for(n;n<nn;n++)                           //ȷ�������������1��1�����׼�������1��1���������
	{
		sum+=fun(n,12,31);
	}
	//printf("%d\n",sum);
	sum=abs(sum-days1+days2);				//ȷ��ʵ�������������
	//printf("%d\n",sum);

	if(y1>=y2)								//���ݸ�����λ�ڻ�׼����ǰ��ȷ�����㹫ʽ
		sum%=7;
	else
		sum=(7-sum%7)%7;

	switch(sum){                            //ƥ�������Ϊ���ڼ�������
	case 0:return 7;break;
		case 1:return 1;break;
			case 2:return 2;break;
				case 3:return 3;break;
					case 4:return 4;break;
						case 5:return 5;break;
							case 6:return 6;break;
	}
}

int month_have_days(int i,int y)		//�����ж�����
{
	int days=0;
	switch(i){
		case 2:
			if(y%4==0&&y%100!=0||y%400==0){
				days+=29;return days;}
			else{
				days+=28;return days;}break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:days+=31;return days;break;

		case 4:
		case 6:
		case 9:
		case 11:days+=30;return days;break;	
		}
}

int main(){
	int y1,m1,d1=1,week,week_have_days,i;
	int y2=2018,m2=1,d2=7;//��׼�գ�����Ϊ������
	int days1=0,days2=0,sum=0;

	printf("������һ����ݼ��·ݣ�����ʾ���·�������\n");
	scanf("%d%d",&y1,&m1);
	printf("%d-%d\n",y1,m1);

	printf("The calender of Month %d of theYear %d\n",m1,y1);
	printf("  SUN  MON  TUE  WED  THU  PRI  SAT\n");
	
	week_have_days=month_have_days(m1,y1);
	days1=fun(y1,m1,d1);                                //����������ǵ���ڶ�����

	for(i=0;i<week_have_days;i++,days1++){
	
			
		week=what_week(y1,y2,m1,m2,d1,d2,days1,days2);	//������µڼ���Ϊ���ڼ�
		
		if(i==0){
			switch(week){
			case 0:printf("   %d ",i+1);break;
			case 1:printf("        %d ",i+1);break;
			case 2:printf("             %d ",i+1);break;
			case 3:printf("                  %d ",i+1);break;
			case 4:printf("                       %d ",i+1);break;
			case 5:printf("                            %d ",i+1);break;
			case 6:printf("                                 %d \n",i+1);break;
			}
		}else if(week==6&&i<10)
			printf("   %d \n",i+1);
		 else if(i<10) 
			printf("   %d ",i+1);
		 else if(week==6&&i>=10)
			printf("   %d\n",i+1);
		 else if(i>=10)
			printf("   %d",i+1);
	
}
	printf("\n");
	system("pause");
}
