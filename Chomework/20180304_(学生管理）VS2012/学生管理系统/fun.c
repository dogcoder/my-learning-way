#include "fun.h"

void system_init(FILE* fp,pacount* pa,pstu_info* ps){
	int ret=0,i=0,ss=0,aa=0;
	pacount		panew,atail=NULL;
	pstu_info	psnew,stail=NULL;
	
	fclose(fp);
	fp=fopen("use_account.txt","r");
	panew=(pacount)calloc(1,sizeof(aco));
	atail=pa[i++]=panew;
	ret=fscanf(fp,"%s\t%s\t%d",panew->usr_name,panew->use_psw,&panew->role);

	while(ret==3){
		panew=(pacount)calloc(1,sizeof(aco));
		pa[i++]=panew;
		ret=fscanf(fp,"%s\t%s\t%d",panew->usr_name,panew->use_psw,&panew->role);
		atail->panext=panew;
		atail=panew;
		aa++;
	}
	pa[i-1]=0;
	free(panew);
	i=0;
/*******************************************����Ϊ�����������˻���������Ϊ������������Ϣ����*********************************/
	fclose(fp);
	fp=fopen("stu_information.txt","r");
	psnew=(pstu_info)calloc(1,sizeof(stu_info));
	stail=ps[i++]=psnew;
	ret=fscanf(fp,"%s\t%s\t%c\t%d\t%d\t%d",psnew->num,psnew->name,&psnew->sex,&psnew->chinese,&psnew->math,&psnew->english);

	while(ret==6){
		psnew=(pstu_info)calloc(1,sizeof(stu_info));
		ps[i++]=psnew;
		ret=fscanf(fp,"%s\t%s\t%c\t%d\t%d\t%d",psnew->num,psnew->name,&psnew->sex,&psnew->chinese,&psnew->math,&psnew->english);
		stail->psnext=psnew;
		stail=psnew;
		ss++;
	}
	ps[i-1]=0;
	free(psnew);
	i=0;
	/*for(i=0;i<ss;i++)
		printf("%s %s %c %d %d %d\n",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);

	for(i=0;i<aa;i++)
		printf("%s %s %d\n",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role );*/
	
}

void screen_title(void){
	printf("**********************************************************************************************************************\n");
	printf("********************************* Student  Information  Management System ********************************************\n");
	printf("**********************************************************************************************************************\n");
	printf("\n");
	printf("\n");
	printf("\n");
}

int role_confirm(pacount* pa,aco input ){
	int i=0;
	while(pa[i]!=NULL){
		if(!strcmp(pa[i]->usr_name,input.usr_name)&&!strcmp(pa[i]->use_psw,input.use_psw)){
			printf("\n\n\n		                       		��½�ɹ���       ");
			system("pause");
			return pa[i]->role;
		}
		i++;
	}
	printf("\n\n\n		                       		��½ʧ�ܣ�       ");
	return -1;
	
}

int system_adm_MENU(void){
	int i=0;
refresh:	
	system("cls");
	screen_title();
	printf("		                       	1.��ѯѧ����Ϣ��\n");
	printf("		                       	2.���ѧ����Ϣ��\n");
	printf("		                       	3.�޸�ѧ����Ϣ��\n");
	printf("		                       	4.ɾ��ѧ����Ϣ��\n\n");
	printf("		                       	5.��ѯ�û��˻���Ϣ��\n");
	printf("		                       	6.����û��˻���Ϣ��\n");
	printf("		                       	7.�޸��û��˻���Ϣ��\n");
	printf("		                       	8.ɾ���û��˻���Ϣ��\n");
	printf("\n		                        9.�˳�ѧ������ϵͳ\n");
	printf("\n\n\n		                        ��������ѡ�˵���       ");
	scanf("%d",&i);
	if(!(i>=1&&i<=9)){
		fflush(stdin);
		goto refresh;
	}
	return i;
}

int system_stu_MENU(void){
	int i=0;
refresh:
	system("cls");
	screen_title();
	printf("		                       	1.��ѯѧ����Ϣ��\n");
	printf("\n					9.�˳�ѧ������ϵͳ\n");
	printf("\n\n\n		                        ��������ѡ�˵���       ");
	scanf("%d",&i);
	if(i!=1&&i!=9){
		fflush(stdin);
		goto refresh;
	}
	return i;
}

int admin_search_stu_info(void){
	int i=-1;
refresh:
	system("cls");
	screen_title();
	printf("		                       	0.��ѯ����ѧ����Ϣ��\n");
	printf("		                       	1.ͨ��ID��ѯѧ����Ϣ��\n");
	printf("		                       	2.ͨ��������ѯѧ����Ϣ��\n");
	printf("		                       	3.return\n");

	printf("\n\n\n		                        ��������ѡ�˵���\n");
	scanf("%d",&i);
	if(!(i>=0&&i<=3)){
		fflush(stdin);
		goto refresh;
	}
	
	return i;
}

void search_all_stu(pstu_info* ps){
	int i=0;
	system("cls");
	screen_title();
	for(i=0;ps[i]!=NULL;i++)
		printf("		                       	%s %s %c %d %d %d\n",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);
}

void serach_stu_by_ID(pstu_info* ps){
	int i=0;
	char n[20]={0};
	system("cls");
	screen_title();
	printf("		                       	�����������ѯID���룺");
	scanf("%s",n);
	printf("\n");
	
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(n,ps[i]->num)==0){
			printf("		                       	ID search success!\n");
			printf("		                       	%s %s %c %d %d %d",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);
			break;
		}
	}
	if(ps[i]==NULL){
		printf("		                       	����ʧ�ܣ���������ȷ��Ϣ��\n");
		fflush(stdin);
	}
}

void serach_stu_by_name(pstu_info* ps){
	int i=0;
	char n[20]={0};
	system("cls");
	screen_title();
	printf("		                       	�����������ѯ������");
	scanf("%s",n);
	printf("\n");
	
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(n,ps[i]->name)==0){
			printf("		                       	name search success!\n");
			printf("		                       	%s %s %c %d %d %d",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);
			break;
		}
	}
	if(ps[i]==NULL){
		printf("		                       	����ʧ�ܣ���������ȷ��Ϣ��\n");
		fflush(stdin);
	}
}

void add_stu_info(pstu_info* ps){
	int i=0;
	pstu_info psnew;
refresh:	
	psnew=(pstu_info)calloc(1,sizeof(stu_info));
	system("cls");
	screen_title();
	printf("		                       	��������ѧ����Ϣ����ʽ���£�\n");
	printf("		                        ѧ��\\t����\\t�Ա�F/M��\\t���ĳɼ�\\t��ѧ�ɼ�\\tӢ��ɼ�\n");
	printf("		                        ");
	scanf("%s\t%s\t%c\t%d\t%d\t%d",psnew->num,psnew->name,&psnew->sex,&psnew->chinese,&psnew->math,&psnew->english);
	
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(psnew->num,ps[i]->num)==0){
			printf("ѧ���Ѵ��ڣ����������룡");
			fflush(stdin);
			system("pause");
			goto refresh;
		}
	}


	for(i=0;ps[i]!=NULL;i++);
	ps[i-1]->psnext=psnew;
	ps[i]=psnew;
	ps[i]->psnext=NULL;
	ps[i+1]=NULL;

	for(i=0;ps[i]!=NULL;i++)
		printf("\n		                        %s %s %c %d %d %d",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);
	printf("\n");
}

void modify_stu_txt_content(pstu_info* ps,FILE* fp){
	int i;
	fclose(fp);
	fp=fopen("stu_information.txt","w");

	for(i=0;ps[i]!=NULL;i++)
			fprintf(fp,"%s\t%s\t%c\t%d\t%d\t%d\n",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);
	fclose(fp);
	fp=fopen("stu_information.txt","r");
}

void update_stu_info(pstu_info* ps){
	int i,find=0;
	char num[20];
refresh:
	system("cls");
	screen_title();
	for(i=0;ps[i]!=NULL;i++)
		printf("\n		                        %s %s %c %d %d %d",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);

	printf("\n		                        (����#�˳�)��������Ҫ�޸ĵ�ѧ��ѧ�ţ�ѧ�Ų����޸ģ���:");
	scanf("%s",num);
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(num,ps[i]->num)==0){
			printf("		                         ���ҳɹ�������������Ϣ:����\\t�Ա�F/M��\\t���ĳɼ�\\t��ѧ�ɼ�\\tӢ��ɼ�\n");
			printf("						 	      :");
			scanf("%s\t%c\t%d\t%d\t%d",ps[i]->name,&ps[i]->sex,&ps[i]->chinese,&ps[i]->math,&ps[i]->english);
			break;
		}
	}
	if(strcmp(num,"#")==0)
		return;
	if(ps[i]==NULL){
		printf("		                        ����ʧ�ܣ���������������Ϣ:");
		system("pause");
		fflush(stdin);
		goto refresh;
	}

	system("cls");
	screen_title();
	for(i=0;ps[i]!=NULL;i++)
		printf("\n		                        %s %s %c %d %d %d",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);
		printf("\n");

}


void delete_stu_txt_content(pstu_info* ps){
	int i=0,j=0;
	char num[20];
refresh:
	system("cls");
	screen_title();
	for(i=0;ps[i]!=NULL;i++)
		printf("\n		                        %s %s %c %d %d %d",ps[i]->num,ps[i]->name,ps[i]->sex,ps[i]->chinese,ps[i]->math,ps[i]->english);

	printf("\n		                        (����#�˳�)��������Ҫɾ����ѧ��ѧ��:");
	scanf("%s",num);
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(num,ps[i]->num)==0){
			if(i==0){
				for(j=i;ps[j]!=NULL;j++)
					ps[j]=ps[j+1];
			}else{
				ps[i-1]->psnext=ps[i]->psnext;
				for(j=i;ps[j]!=NULL;j++)
					ps[j]=ps[j+1];
			}
			printf("		                        ɾ���ɹ���\n");
			system("pause");
			break;
		}
	}

	if(strcmp(num,"#")==0)
		return;

	if(ps[i]==NULL){
		printf("		                        ����ʧ�ܣ�����������ѧ��ѧ��:");
		fflush(stdin);
		system("pause");
		goto refresh;
	}
}

void add_aco_info(pacount* pa){
	int i=0;
	pacount psnew;
refresh:	
	psnew=(pacount)calloc(1,sizeof(aco));
	system("cls");
	screen_title();
	printf("		                       	���������˻���Ϣ����ʽ���£�\n");
	printf("		                       �ʻ���\\t����\\tȨ�ޣ�1Ϊ����Ա��2Ϊѧ����\n");
	printf("		                        ");
	scanf("%s\t%s\t%d",psnew->usr_name,psnew->use_psw,&psnew->role );
	
	for(i=0;pa[i]!=NULL;i++){
		if(strcmp(psnew->usr_name,pa[i]->usr_name)==0){
			printf("�˻��Ѵ��ڣ����������룡");
			fflush(stdin);
			system("pause");
			goto refresh;
		}
	}


	for(i=0;pa[i]!=NULL;i++);
	pa[i-1]->panext=psnew;
	pa[i]=psnew;
	pa[i]->panext=NULL;
	pa[i+1]=NULL;

	for(i=0;pa[i]!=NULL;i++)
		printf("\n		                        %s %s %d",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role);
}

void modify_aco_txt_content(pacount* pa,FILE* fp){
	int i;
	fclose(fp);
	fp=fopen("use_account.txt","w");

	for(i=0;pa[i]!=NULL;i++)
		fprintf(fp,"%s\t%s\t%d\n",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role);
	fclose(fp);
	fp=fopen("use_account.txt","r");
}

void serach_aco_all(pacount*pa){
	int i=0;
	system("cls");
	screen_title();
	for(i=0;pa[i]!=NULL;i++)
		printf("\n		                        %s %s %d",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role);
	printf("\n\n		                        ");
 
}

void update_aco_info(pacount* pa){
	int i,find=0;
	char num[20];
refresh:
	system("cls");
	screen_title();
	for(i=0;pa[i]!=NULL;i++)
		printf("\n		                        %s %s %d",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role);
	printf("\n		                        (����#�˳�) ��������Ҫ�޸ĵ��˻������˻��������޸ģ���:");
	scanf("%s",num);
	for(i=0;pa[i]!=NULL;i++){
		if(strcmp(num,pa[i]->usr_name)==0){
			printf("\n\n		                         ���ҳɹ���\n\n		                         ����������Ϣ:�˻�����\\tȨ�ޣ�1 ����Աor2 ѧ����\n");
			printf("						     :");
			scanf("%s\t%d",pa[i]->use_psw,&pa[i]->role );
			break;
		}
	}
	if(strcmp(num,"#")==0)
		return;
	if(pa[i]==NULL){
		printf("		                        ����ʧ�ܣ���������������Ϣ:");
		system("pause");
		fflush(stdin);
		goto refresh;
	}

	system("cls");
	screen_title();
	for(i=0;pa[i]!=NULL;i++)
		printf("\n		                        %s %s %d",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role);
		printf("\n");

}

void delete_aco_txt_content(pacount* pa){
	int i=0,j=0;
	char num[20];
refresh:
	system("cls");
	screen_title();
	for(i=0;pa[i]!=NULL;i++)
		printf("\n		                        %s %s %d",pa[i]->usr_name,pa[i]->use_psw,pa[i]->role);

	printf("\n		                        (����#�˳�)��������Ҫɾ�����˺���Ϣ:");
	scanf("%s",num);
	for(i=0;pa[i]!=NULL;i++){
		if(strcmp(num,pa[i]->usr_name)==0){
			if(i==0){
				for(j=i;pa[j]!=NULL;j++)
					pa[j]=pa[j+1];
			}else{
				pa[i-1]->panext=pa[i]->panext;
				for(j=i;pa[j]!=NULL;j++)
					pa[j]=pa[j+1];
			}
			printf("		                        ɾ���ɹ���\n");
			system("pause");
			break;
		}
	}
	if(strcmp(num,"#")==0)
		return;

	if(pa[i]==NULL){
		printf("		                        ����ʧ�ܣ������������˺�:");
		fflush(stdin);
		system("pause");
		goto refresh;
	}
}

int stu_search_stu_info(void){
	int i=-1;
refresh:
	system("cls");
	screen_title();
	printf("		                       	1.ͨ��ID��ѯѧ����Ϣ��\n");
	printf("		                       	2.ͨ��������ѯѧ����Ϣ��\n");
	printf("		                       	3.return\n");

	printf("\n\n\n		                        ��������ѡ�˵���       ");
	scanf("%d",&i);
	if(!(i>=1&&i<=3)){
		fflush(stdin);
		goto refresh;
	}
	
	return i;
}