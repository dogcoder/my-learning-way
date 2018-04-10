#include <stdio.h>
#include <stdlib.h>
 
void fun(void){
	int i,j,k=4;
	int t;	
	for(i=0;i<5;i++){
		for(j=0;j<k;j++)
			printf(" ");
	    t=1; 
		for(;j<5+i;j++){
			
			if( t==1){
				printf("*");
				 t=0;
			}else {
				printf(" ");
				t=1;
			}	
		}
		printf("\n");
		k--;
	}
	k=1;
	for(i=0;i<5;i++){
		for(j=0;j<k;j++)
			printf(" ");
		t=1; 
		for(;j<9-i;j++){
			
			if( t==1){
				printf("*");
				 t=0;
			}else {
				printf(" ");
				t=1;
			}	
		}
		printf("\n");
		k++;
	}

}


int main()
{
	fun();

	system("pause");
}

