#include <stdio.h>
#include <stdlib.h>

#define N 100

int input(char *a){
	int i=0,count=0;
	char* p=a,c;
	while((c=getchar())!='\n'){
			*p++=c;
			count++;	
		}
	*p='\0';
	return count;
}

void myprinput(char *a,int count){
	int i;

	printf("大整数为：        ");
	for(i=0;i<count;i++)
		printf("%c",a[i]);
	
	printf("   count=%d \n",count);
}

void add(char* a,int counta,char* b,int countb,char*c){
	char *pa,*pb,*pc;
	int x,y,z=0;
	
	pa=a;
	pb=b;
	pc=c;

	
	while(counta>0&&countb>0){
		x=*(pa+counta-1)-48;
		y=*(pb+countb-1)-48;
		if(x+y+z>=10&&z==1){                    //同位相加大于等于10，且后位进1
			z=1;
			*pc=(x+y+1)%10+48;
			pc++;
		}else if(x+y>=10&&z==0){             //同位相加大于等于10，且后位进0
			z=1;
			*pc=(x+y)%10+48;
			pc++;
		}else if(x+y+z<10&&z==1){              //同位相加小于10，且后位进1
			z=0;
			*pc=x+y+1+48;
			pc++;
		}else if(x+y<10&&z==0){              //同位相加小于10，且后位进0
			z=0;
			*pc=x+y+48;
			pc++;
		}
		counta--;
		countb--;
	}	
	
	while(counta>0&&countb==0)
	{
		if(z==1){
			x=*(pa+counta-1)-48;
			*pc=(x+z)%10+48;
			if(x+z>=10)
				z=1;
			else
				z=0;
		}else{
			x=*(pa+counta-1)-48;
			*pc=x+48;
		}
		pc++;
		counta--;
	}
	while(counta==0&&countb>0)
	{
		if(z==1){
			y=*(pb+countb-1)-48;
			*pc=(y+z)%10+48;
			if(x+z>=10)
				z=1;
			else
				z=0;
		}else{
			y=*(pb+countb-1)-48;
			*pc=y+48;
		}
		pc++;
		countb--;
	}
	if(z==1){
		*pc='1';
		*(pc+1)='\0';
	}else
		*pc='\0';
}



int main(){
	char a[N],b[N],c[N];
	int i=0,counta=0,countb=0,countc=0;
	
	counta=input(a);
	countb=input(b);
	
	myprinput(a,counta);
	myprinput(b,countb);

	add(a,counta,b,countb,c);
	for(i=0;c[i]!='\0';i++)
		countc++;

	printf("两个大整数之和为:");
	for(i=countc;i>=0;i--)
		printf("%c",c[i]);
	printf("  countc=%d\n",countc);
		

	system("pause");
}
