#ifndef __HEAD_H__
#define __HEAD_H_

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
#include <crypt.h>
#include <math.h>
#include<openssl/md5.h>

typedef struct{
	int len;					//传送字节数
	char buf[1000];
}train;

int cli_land(int socfd);	//注册+登陆

int send_n(int fd,char* file,int len);

int recv_n(int fd, char*file,int len);

int recv_info(int socfd,char* thepwd);		//接受文件函数

int trans_info(int fd,char* FILENAME,char* thepwd);	//发送文件

void sendcomd(char*,char*,int socfd);		//发送两条命令

void sendcomd1(char* comd ,int socfd);		//发送一条

void recvcomd1(char* comd,int socfd);		//接受一条

void salt_password(char* us_psw);			//合成密文

void salt_merge(char* salt,char* pwd);		//用户端合成密文

int cal_MD5(char* FileName,unsigned char* myMD5);	//计算MD5  

#endif
