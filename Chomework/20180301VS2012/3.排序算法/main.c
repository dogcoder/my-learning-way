#include "func.h"

int main()
{
	int *a;
	int i;
	time_t begin,end;
	a=(int*)malloc(N*sizeof(int));
	srand(time(NULL));
	for(i=0;i<N;i++)
	{
		a[i]=rand()%100;
	}
	//print(a);
	begin=time(NULL);
	//arr_select(a);
	//arr_insert(a);
	
	//arr_quick(a,0,N-1);
	//qsort(a,N,sizeof(int),compare);
	arr_heap(a);
	end=time(NULL);
	printf("use time=%d\n",end-begin);
	//print(a);
	system("pause");
	return 0;
}