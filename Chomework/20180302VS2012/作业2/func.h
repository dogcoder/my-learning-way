#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 200000

typedef struct abc{
	char cc[30];
	int num;
	struct abc* next;
}abc,*pabc;

void change_big_to_small(FILE* fp);	//改变大写字母变为小写字母（代码有问题）
long zifu_num(long *a,FILE* fp);		//统计字符总数
int word_num_and_word_FM(FILE* fp,pabc* words);//将单词存入链表，并使结构体指针数组指向各个链表节点；

int compare(const void *pleft, const void *pright);