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
/*******************************************上面为建立并输入账户链表，下面为建立并输入信息链表*********************************/
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
			printf("\n\n\n		                       		登陆成功！       ");
			system("pause");
			return pa[i]->role;
		}
		i++;
	}
	printf("\n\n\n		                       		登陆失败！       ");
	return -1;
	
}

int system_adm_MENU(void){
	int i=0;
refresh:	
	system("cls");
	screen_title();
	printf("		                       	1.查询学生信息：\n");
	printf("		                       	2.添加学生信息：\n");
	printf("		                       	3.修改学生信息：\n");
	printf("		                       	4.删除学生信息：\n\n");
	printf("		                       	5.查询用户账户信息：\n");
	printf("		                       	6.添加用户账户信息：\n");
	printf("		                       	7.修改用户账户信息：\n");
	printf("		                       	8.删除用户账户信息：\n");
	printf("\n		                        9.退出学生管理系统\n");
	printf("\n\n\n		                        请输入所选菜单：       ");
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
	printf("		                       	1.查询学生信息：\n");
	printf("\n					9.退出学生管理系统\n");
	printf("\n\n\n		                        请输入所选菜单：       ");
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
	printf("		                       	0.查询所有学生信息：\n");
	printf("		                       	1.通过ID查询学生信息：\n");
	printf("		                       	2.通过姓名查询学生信息：\n");
	printf("		                       	3.return\n");

	printf("\n\n\n		                        请输入所选菜单：\n");
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
	printf("		                       	请输入所需查询ID号码：");
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
		printf("		                       	搜索失败，请输入正确信息！\n");
		fflush(stdin);
	}
}

void serach_stu_by_name(pstu_info* ps){
	int i=0;
	char n[20]={0};
	system("cls");
	screen_title();
	printf("		                       	请输入所需查询姓名：");
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
		printf("		                       	搜索失败，请输入正确信息！\n");
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
	printf("		                       	请输入新学生信息，格式如下：\n");
	printf("		                        学号\\t姓名\\t性别（F/M）\\t语文成绩\\t数学成绩\\t英语成绩\n");
	printf("		                        ");
	scanf("%s\t%s\t%c\t%d\t%d\t%d",psnew->num,psnew->name,&psnew->sex,&psnew->chinese,&psnew->math,&psnew->english);
	
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(psnew->num,ps[i]->num)==0){
			printf("学号已存在，请重新输入！");
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

	printf("\n		                        (输入#退出)请输入需要修改的学生学号（学号不能修改！）:");
	scanf("%s",num);
	for(i=0;ps[i]!=NULL;i++){
		if(strcmp(num,ps[i]->num)==0){
			printf("		                         查找成功！请输入新信息:姓名\\t性别（F/M）\\t语文成绩\\t数学成绩\\t英语成绩\n");
			printf("						 	      :");
			scanf("%s\t%c\t%d\t%d\t%d",ps[i]->name,&ps[i]->sex,&ps[i]->chinese,&ps[i]->math,&ps[i]->english);
			break;
		}
	}
	if(strcmp(num,"#")==0)
		return;
	if(ps[i]==NULL){
		printf("		                        查找失败！请重新输入新信息:");
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

	printf("\n		                        (输入#退出)请输入需要删除的学生学号:");
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
			printf("		                        删除成功！\n");
			system("pause");
			break;
		}
	}

	if(strcmp(num,"#")==0)
		return;

	if(ps[i]==NULL){
		printf("		                        查找失败！请重新输入学生学号:");
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
	printf("		                       	请输入新账户信息，格式如下：\n");
	printf("		                       帐户名\\t密码\\t权限（1为管理员，2为学生）\n");
	printf("		                        ");
	scanf("%s\t%s\t%d",psnew->usr_name,psnew->use_psw,&psnew->role );
	
	for(i=0;pa[i]!=NULL;i++){
		if(strcmp(psnew->usr_name,pa[i]->usr_name)==0){
			printf("账户已存在，请重新输入！");
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
	printf("\n		                        (输入#退出) 请输入需要修改的账户名（账户名不能修改！）:");
	scanf("%s",num);
	for(i=0;pa[i]!=NULL;i++){
		if(strcmp(num,pa[i]->usr_name)==0){
			printf("\n\n		                         查找成功！\n\n		                         请输入新信息:账户密码\\t权限（1 管理员or2 学生）\n");
			printf("						     :");
			scanf("%s\t%d",pa[i]->use_psw,&pa[i]->role );
			break;
		}
	}
	if(strcmp(num,"#")==0)
		return;
	if(pa[i]==NULL){
		printf("		                        查找失败！请重新输入新信息:");
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

	printf("\n		                        (输入#退出)请输入需要删除的账号信息:");
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
			printf("		                        删除成功！\n");
			system("pause");
			break;
		}
	}
	if(strcmp(num,"#")==0)
		return;

	if(pa[i]==NULL){
		printf("		                        查找失败！请重新输入账号:");
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
	printf("		                       	1.通过ID查询学生信息：\n");
	printf("		                       	2.通过姓名查询学生信息：\n");
	printf("		                       	3.return\n");

	printf("\n\n\n		                        请输入所选菜单：       ");
	scanf("%d",&i);
	if(!(i>=1&&i<=3)){
		fflush(stdin);
		goto refresh;
	}
	
	return i;
}