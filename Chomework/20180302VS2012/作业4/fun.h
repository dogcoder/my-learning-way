#include <stdio.h>
#include <stdlib.h>

typedef struct student{
	char number[20];
	char name[20];
	char sex;
	int score1;
	int score2;
	int score3;
	struct student* next;
}stu,*pstu;

void creat_lian(FILE* fp,pstu *head,pstu* tail,pstu* pstu_lian);

int compare(const void* pleft,const void* pright);
void sort_lian(pstu* pstu_lian,int n);