#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 200000

typedef struct abc{
	char cc[30];
	int num;
	struct abc* next;
}abc,*pabc;

void change_big_to_small(FILE* fp);	//�ı��д��ĸ��ΪСд��ĸ�����������⣩
long zifu_num(long *a,FILE* fp);		//ͳ���ַ�����
int word_num_and_word_FM(FILE* fp,pabc* words);//�����ʴ���������ʹ�ṹ��ָ������ָ���������ڵ㣻

int compare(const void *pleft, const void *pright);