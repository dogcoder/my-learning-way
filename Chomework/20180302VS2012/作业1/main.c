#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv){
	FILE* fp;
	char c;
	int i;
	int asc[128]={0};
	if(argc!=2){
		printf("error args\n");
		system("pause");
		return -1;
	}

	fp=fopen(argv[1],"r+");
	
	if(fp==NULL){
		printf("error");
	}

	while((c=fgetc(fp))!=EOF){
		if(c>='A'&&c<='Z'){
			c=c+32;
			fseek(fp,-1,SEEK_CUR);
			fputc(c,fp);
			fseek(fp,0,SEEK_CUR);
		}
	}
	fseek(fp,0,SEEK_SET);
	while((c=fgetc(fp))!=EOF){
		if(!(c>='a'&&c<='z'||c==' '||c=='\n')){
			c=' ';
			fseek(fp,-1,SEEK_CUR);
			fputc(c,fp);
			fseek(fp,0,SEEK_CUR);
		}
	}
	fclose(fp);
	system("pause");
}
