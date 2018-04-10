#include "func.h"


int main(int argc,char* argv[]){
	FILE* fp; 
	pabc* words=(pabc*)calloc(N,sizeof(pabc));
	long number[129]={0};
	long wordsum=0,line=0,word=0;
	int i,hangnum=0,wordsnumber=0;
	if(argc!=2){
		printf("error argc!\n");
		system("pause");
		return -1;
	}

	fp=fopen(argv[1],"r+");

	if(fp==NULL){
		perror("fopen");
		return -1;
	}                             //定义文件指针并测试
/***********************************************************************************/
	change_big_to_small(fp);			//将大写字母改为小写
	fseek(fp,0,SEEK_SET);

	wordsum=zifu_num(number,fp);
	hangnum=number[128];
	printf("字符数为: %ld\n",wordsum);
	printf("行数为 : %ld\n",hangnum);
	/*for(i=0;i<128;i++)
		printf("a[%d]=%d \n",i,number[i]);     */             //测试各字符分别含有量和总量
/*********************************************************************************/ 
	fseek(fp,0,SEEK_SET);
	wordsnumber=word_num_and_word_FM(fp,words);
	printf("单词数为：%d\n",wordsnumber);
	for(i=0;i<10;i++){
		printf(" 词频第 %d 位 为：%s 词频为 %d \n",i+1,words[i]->cc,words[i]->num);
	}

	fclose(fp);
	system("pause");
}
