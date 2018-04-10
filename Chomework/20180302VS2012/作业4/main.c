#include "fun.h"


int main(int argc,char* argv[]){
	FILE* fp;
	pstu stu_lian[20];
	pstu head,tail;
	int i=0;

	head=tail=NULL;
	
	if(argc!=2){
		printf("error !");
		system("pause");
		return -1;
	}

	fp=fopen(argv[1],"r+");

	if(fp==NULL){
		perror("fopen");
		system("pause");
		return -1;
	}
/************************************/   //建立文件指针并测试，建立变量；
	creat_lian(fp,&head,&tail,stu_lian);
	sort_lian(stu_lian,5);

	while(stu_lian[i]->next!=NULL){
		printf("%s\n",stu_lian[i++]->name);
	}
	fseek(fp,0,SEEK_SET);
	i=0;
	while(stu_lian[i]->next!=NULL){
		fprintf(fp,"%s\t%s\t%c\t%d\t%d\t%d\n",stu_lian[i]->number,stu_lian[i]->name,stu_lian[i]->sex,stu_lian[i]->score1,stu_lian[i]->score2,stu_lian[i]->score3);
		i++;
	}
	fclose(fp);
	system("pause");	
}