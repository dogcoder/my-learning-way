#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <math.h>
#include <mysql/mysql.h>
#include <sys/sendfile.h>

int cd_comdfunc(char* arg,int socfd,char* pwd,char* USERNAME,char* NowDir); //cd处理函数

int ls_comdfunc(int,const char*);			//ls处理函数

int mkdir_comdfunc(int socfd,char* name,char* thepwd,char* NowDir,char* USERNAME);		//mkdir 处理函数

int cli_land_confirm(int socfd,char* USERNAME);			//客户端登陆及注册函数

int sendfile_n(int socfd,int fd,size_t size);	

void recvcomd1(char* comd,int socfd);		//接受一条命令

void recvcomd2(char* comd,char* arg,int socfd);	//接受命令、参数或者账户密码

void sendcomd1(char* comd ,int socfd);		//发送一条确认命令

void sendcomd2(char* comd ,char* arg,int socfd);	//发送命令及参数

int mysql_user_register(char* UserName,char* oldpwd);	//新用户注册信息输入Mysql

int mysql_confirm_NOsameUser(char* UserName);		//注册时用户名查重

int mysql_fine_salt(char* UserName,char* salt);		//注册时用户名查重

int mysql_psw_verify(char* UserName,char* psw);		//密码验证

void user_O_F_line_record(char* UserName,char* Style);	//用户上线 下线记录

void msql_user_operation(char* UserName,char* Command,char* Arguments);	//用户操作 记录

int mysql_UserFile_insert(char* NowDir,char* Filename,char* Filetype,char* MD5,char* User,char* AbsRoad);		//用户文件录入

int mysql_find_KeyCode(char* NowDir,char* User);		//根据当前文件夹及文件夹所属用户确定 寻找code 填入precode

int mysql_find_MD5(char* myMD5);		//根据客户端所发送MD5码 验证服务端是否存在该文件

void mysql_find_AbsRoad(char* MD5,char* myroad);		//根据当前文件MD5码，寻找绝对路径用于硬链接

int mysql_delete_UserFile(char* Filename,char* User);	//根据文件名及所属用户删除表中信息
#endif
