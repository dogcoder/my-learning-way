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
int system_adm_MENU(void);	//一级管理选项菜单
int system_stu_MENU(void);	//一级学生选项菜单

int admin_search_stu_info(void);  //二级管理搜索信息菜单

void search_all_stu(pstu_info* ps); //功能实现：输出所有学生信息
void serach_stu_by_ID(pstu_info* ps);//功能实现:通过ID查询学生信息
void serach_stu_by_name(pstu_info* ps);//功能实现：通过姓名查询学生信息
void add_stu_info(pstu_info* ps);//功能实现：增加学生信息
void modify_stu_txt_content(pstu_info* ps,FILE* fp);//功能实现，刷新信息文本文件，将链表信息重新存储其中
void update_stu_info(pstu_info* ps);//功能实现：修改学生信息
void delete_stu_txt_content(pstu_info* ps);//功能实现：删除学生信息

void add_aco_info(pacount* pa);//功能实现：增加账户信息
void modify_aco_txt_content(pacount* pa,FILE* fp);//功能实现，刷新账户文本文件，将链表信息重新存储其中
void serach_aco_all(pacount*pa);//功能实现：输出所有账户信息
void update_aco_info(pacount* pa);//功能实现：修改账户信息
void delete_aco_txt_content(pacount* pa);//功能实现：删除账户信息

int stu_search_stu_info(void);//二级学生搜索信息菜单