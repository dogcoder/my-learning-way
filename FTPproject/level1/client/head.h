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

typedef struct{
	int len;					//传送字节数
	char buf[1000];
}train;

int send_n(int fd,char* file,int len);

int recv_n(int fd, char*file,int len);

int recv_info(int socfd,char* thepwd);		//接受文件函数

int trans_info(int fd,char* FILENAME,char* thepwd);	//发送文件

#endif
