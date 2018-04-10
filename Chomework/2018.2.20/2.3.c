#include <stdlib.h>
#include <stdio.h>
#define N 9

void fun(void){
	int i,j;

	for(i=1;i<20;i++){
		for(j=1;j<20;j++){
			if(abs((i+j-4)-10)<=5&&abs(i-j+5)<=4&&abs(i+j)%2==0)
				printf(" ");
			else if(abs((i+j)-20)<=8&&abs(i-j)<=8&&abs(i+j)%2==0)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

int main(){
	fun();

	system("pause");
}

