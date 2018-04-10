#include "fun.h"

void creat_lian(FILE* fp,pstu *head,pstu* tail,pstu* pstu_lian){
	pstu pnew,pcur;
	int ret=0,i=0;
	pnew=(pstu)calloc(1,sizeof(stu));
	*head=*tail=pstu_lian[i++]=pnew;
	ret=fscanf(fp,"%s\t%s\t%c\t%d\t%d\t%d",pnew->number,pnew->name,&pnew->sex,&pnew->score1,&pnew->score2,&pnew->score3);

	while(ret==6){
		pnew=(pstu)calloc(1,sizeof(stu));
		pstu_lian[i++]=pnew;
		ret=fscanf(fp,"%s\t%s\t%c\t%d\t%d\t%d",pnew->number,pnew->name,&pnew->sex,&pnew->score1,&pnew->score2,&pnew->score3);
		(*tail)->next=pnew;
		*tail=pnew;
	}
	pcur=*head;

	while(pcur->next!=NULL){
		printf("%s\t%s\t%c\t%d\t%d\t%d\n",pcur->number,pcur->name,pcur->sex,pcur->score1,pcur->score2,pcur->score3);
		pcur=pcur->next;
	}

}


void sort_lian(pstu* pstu_lian,int n){
	qsort(pstu_lian,n,sizeof(pstu_lian),compare);
}

int compare(const void* pleft,const void* pright){
	pstu* p1=(pstu*)pleft;
	pstu* p2=(pstu*)pright;

	if((*p1)->score1+(*p1)->score2+(*p1)->score3  <  (*p2)->score1+(*p2)->score2+(*p2)->score3)
		return 1;
	else if((*p1)->score1+(*p1)->score2+(*p1)->score3  >  (*p2)->score1+(*p2)->score2+(*p2)->score3)
		return -1;
	else 
		return 0;
}
