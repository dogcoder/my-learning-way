#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


typedef struct stu{	
	char num[20];
	char name[20];
	char sex;
	int chinese;
	int math;
	int english;
	struct stu* psnext;
}stu_info,*pstu_info;


typedef struct acount{
	char usr_name[20];
	char use_psw[20];
	int role;
	struct acount* panext; 
}aco,*pacount;


void system_init(FILE* fp,pacount* pa,pstu_info* ps);
void screen_title(void);
int role_confirm(pacount* pa,aco input );
int system_adm_MENU(void);	//һ������ѡ��˵�
int system_stu_MENU(void);	//һ��ѧ��ѡ��˵�

int admin_search_stu_info(void);  //��������������Ϣ�˵�

void search_all_stu(pstu_info* ps); //����ʵ�֣��������ѧ����Ϣ
void serach_stu_by_ID(pstu_info* ps);//����ʵ��:ͨ��ID��ѯѧ����Ϣ
void serach_stu_by_name(pstu_info* ps);//����ʵ�֣�ͨ��������ѯѧ����Ϣ
void add_stu_info(pstu_info* ps);//����ʵ�֣�����ѧ����Ϣ
void modify_stu_txt_content(pstu_info* ps,FILE* fp);//����ʵ�֣�ˢ����Ϣ�ı��ļ�����������Ϣ���´洢����
void update_stu_info(pstu_info* ps);//����ʵ�֣��޸�ѧ����Ϣ
void delete_stu_txt_content(pstu_info* ps);//����ʵ�֣�ɾ��ѧ����Ϣ

void add_aco_info(pacount* pa);//����ʵ�֣������˻���Ϣ
void modify_aco_txt_content(pacount* pa,FILE* fp);//����ʵ�֣�ˢ���˻��ı��ļ�����������Ϣ���´洢����
void serach_aco_all(pacount*pa);//����ʵ�֣���������˻���Ϣ
void update_aco_info(pacount* pa);//����ʵ�֣��޸��˻���Ϣ
void delete_aco_txt_content(pacount* pa);//����ʵ�֣�ɾ���˻���Ϣ

int stu_search_stu_info(void);//����ѧ��������Ϣ�˵�