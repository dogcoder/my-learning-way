#include "fun.h"


int main(int argc,char* argv[]){
	FILE* fp;
	char c;
	int i=0,role=0,x=0,xx=0,sx=0;
	aco _input;
	pacount heada=NULL,taila=NULL;			//�˻�����ͷβָ��
	pstu_info heads=NULL,tails=NULL;		//��Ϣ����ͷβָ��
	pacount pa[20]={0};				//�˻��ṹ��ָ������
	pstu_info ps[20]={0};			//��Ϣ�ṹ��ָ������
	if(argc!=2){
		printf("file is error");
		system("pause");
		return -1;
	}
	fp=fopen("configre.txt","r+");
	if(fp==NULL){
		perror("fopen");
		system("pause");
		return -1;
	}
/*********************************************�ϣ����弰У���ļ�ָ��***********************************/
	system_init(fp,pa,ps);			//��ʼ��

	system("cls");
	screen_title();
	printf("                                      �������ʻ�����");
	scanf("%s",&_input.usr_name);printf("\n");
	printf("                                      ��������������");
	while((c=getch())!='\r'){
		_input.use_psw[i]=c;
		if(c=='\b'){
			printf("\b \b");
		}
		else 
			putchar('*');
		i++;
	}
	_input.use_psw[i]='\0';
	role=role_confirm(pa,_input);
	if(role==-1)
		goto ending;
	else if(role==1)
		goto adm_screen;
	else if(role==2)
		goto stu_screen;
	else{
		system("cls");
		screen_title();
		printf("\n\n\n		                       		�˻�Ȩ�޴���ϵͳ������\n");
		goto ending;
	}
/**********************************��֤�˻���¼��Ϣ����ת��ӦȨ�޽���***********************************/
adm_screen:
	x=system_adm_MENU();
	switch(x){
	case 1:{ 
		adm_screen_1:
			xx=admin_search_stu_info();
			if(xx==0){
				search_all_stu(ps);
				system("pause");
				goto adm_screen_1;
			}else if(xx==1){
				serach_stu_by_ID(ps);
				system("pause");
				goto adm_screen_1;
			}else if(xx==2){
				serach_stu_by_name(ps);
				system("pause");
				goto adm_screen_1;
			}else if(xx==3){
				goto adm_screen;
			}
				goto adm_screen_1;
		  		   }
	case 2:  {
		 add_stu_info(ps);
		 modify_stu_txt_content(ps,fp);
		 system("pause");
		 goto adm_screen;
			 }
	case 3:{
		update_stu_info(ps);
		modify_stu_txt_content(ps,fp);
		system("pause");
		goto adm_screen;
		   }
	case 4: {
		delete_stu_txt_content(ps);
		modify_stu_txt_content(ps,fp);
		system("pause");
		goto adm_screen;
		   }
	case 5: {
		serach_aco_all(pa);
		system("pause");
		goto adm_screen;
		   }
	case 6:  {
		add_aco_info(pa);
		modify_aco_txt_content(pa,fp);
		system("pause");
		goto adm_screen;
		   }
	case 7:  {
		update_aco_info(pa);
		modify_aco_txt_content(pa,fp);
		system("pause");
		goto adm_screen;
		   }
	case 8: {
		delete_aco_txt_content(pa);
		modify_aco_txt_content(pa,fp);
		system("pause");
		goto adm_screen;
		   }
	case 9:  goto ending;
	
	goto adm_screen;
	}
/*********************************************����Ϊ����Ա��������*********************************/	
stu_screen:
	x=system_stu_MENU();
	switch(x){
	case 1:  {
		stu_screen_1:
			sx=stu_search_stu_info();
			 if(sx==1){
				serach_stu_by_ID(ps);
				system("pause");
				goto stu_screen_1;
			}else if(sx==2){
				serach_stu_by_name(ps);
				system("pause");
				goto stu_screen_1;
			}else if(sx==3){
				goto stu_screen;
			}  		  
		goto stu_screen;
			 }
	case 9: goto ending;  

	goto stu_screen;
	}
/*******************************************����Ϊѧ�������˵�***********************************************/



/*******************************************ϵͳ����*******************************************************/
	fclose(fp);
ending:
	system("pause");
}
