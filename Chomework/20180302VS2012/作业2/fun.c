#include "func.h"

long zifu_num(long *a,FILE* fp){		//�����ַ����� ����������������a[128]
	 char i;
	 long sum=0;
	 int hang=0;
	 int k;
	 while((i=fgetc(fp))!=EOF){
		 if(i==' ')
			 continue;
		 a[i]++;
		 if(i=='\n')
			 hang++;
	 }
	 a[128]=hang+1;
	 for(k=0;k<128;k++)
		sum+=a[k];
	 return sum;
}


void change_big_to_small(FILE* fp){		//����д��ĸ��ΪСд��ĸ
	char c;
	printf("�ַ��ı俪ʼ��\n");
	while((c=fgetc(fp))!=EOF){
		if(c>='A'&&c<='Z'){
			c=c+32;
			fseek(fp,-1,SEEK_CUR);
			fputc(c,fp);
			fseek(fp,0,SEEK_CUR);
		}
	}
	printf("�ַ��ı���ɣ�\n");
	fseek(fp,0,SEEK_SET);
}	   


int word_num_and_word_FM(FILE* fp,pabc* words){
	int tag=0,i=0,j,number=0,k=0,same=1;
	char c;
	char w[30]={0};
	pabc head=NULL,tail=NULL,pnew;
	printf("��ʼ����Ѱ�ҵ�����������Ƶ�ʣ�\n");

	while((c=fgetc(fp))!=EOF){
		if(!(c>='a'&&c<='z')){			//�ж϶�ȡ�Ƿ�Ϊ��ĸ
			continue;
		}else{
			fseek(fp,-1,SEEK_CUR);		//���ǿո񽫵��ʴ����ַ����顣
			while((c=fgetc(fp))!=EOF&&c>='a'&&c<='z'){
				w[i]=c;
				i++;
			}
			i=0;
		}

		if(head==NULL){				                               //�ж������Ƿ�Ϊ�գ�Ϊ�մ���ͷָ��
			pnew=(pabc)calloc(1,sizeof(abc));
			for(j=0;w[j]!='\0';j++)
				pnew->cc[j]=w[j];
			pnew->num=1;
			words[k]=pnew;	
			k++;
			tail=head=pnew;
			memset(w,'\0',sizeof(w));								  	//���ʴ����������ӵ�ָ������
		}else{	
			for(i=0;i<k;i++){
				if(strcmp(w,words[i]->cc)==0){
					same=0;
					break;	
				}
			}
			if(same==0&&i<=k){
				words[i]->num=(words[i]->num)+1;
				same=1;
				memset(w,'\0',sizeof(w));
			}else{
				pnew=(pabc)calloc(1,sizeof(abc));
				for(j=0;w[j]!='\0';j++)
					pnew->cc[j]=w[j];
				pnew->num=1;
				words[k]=pnew;	
				k++;
				tail->next=pnew;
				tail=pnew;
				memset(w,'\0',sizeof(w));
			}
		}	
		i=0;
}
	qsort(words,k,sizeof(pabc),compare);
	return k;
}

int compare(const void *pleft, const void *pright){
	pabc* p1=(pabc*)pleft;
	pabc* p2=(pabc*)pright;
	if((*p1)->num>(*p2)->num)
		return -1;
	else if((*p1)->num<(*p2)->num)
		return 1;
	else 
		return 0;
}
