#include <stdio.h>
#include <stdlib.h>

int main()
{
	char a[100];
	int i=0,count=0;

	while(fflush(stdin),scanf("%c",&a[i])!=EOF)
	{
		printf("%c = %c\n",a[i],a[i]-32);
		i++;
		count++;
	}


	system("pause");




}
