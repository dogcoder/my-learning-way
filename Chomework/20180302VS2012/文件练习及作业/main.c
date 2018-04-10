#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
	FILE* fp;
	int i;
	char c;

	printf("argc=%d\n",argc);
	for(i=0;i<argc;i++)
	{
		puts(argv[i]);
	}

	fp=fopen(argv[1],"r+");
	if(NULL==fp){
		perror("fopen");
	}

	/*while((c=fgetc(fp))!=EOF){
		putchar(c);
	}*/

	i=fputc('H',fp);
	if(EOF==i){
		perror("fputc");
	}
	fclose(fp);

	system("pause");
}
