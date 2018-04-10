#include <stdio.h>
#include <stdlib.h>


int main(){
	
	long ten;
	int i;
	int a[30],sum=0;

	while(scanf("%ld",&ten)!=EOF){
		printf("你输入了： %ld\n",ten);
		for(i=0;i<30&&ten>0;i++){
			a[i]=ten%2;
			ten/=2;
		}

		for(;i>0;i--){
			if(a[i-1]==1) sum++;
			printf("%d",a[i-1]);
		}
		printf("  1有%d个\n",sum);
		printf("\n");

		sum=0;
	}

	system("pause");
}
