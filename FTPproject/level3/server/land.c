#include "head.h"
#include "factory.h"
//用户注册及登陆

int cli_land_confirm(int socfd,char* USERNAME)		//客户端登陆及注册函数
{
	char salt[15]={0};
	char user[500];
	char pwd[500];
	int key;
	int ret;
restart:						//注册失败则重新接受
	recv(socfd,&key,4,0);

	if(key==1){
		printf("新用户注册\n");
		recvcomd2(user,pwd,socfd);
		printf("%s \n%s \n",user,pwd);
		ret=mysql_user_register(user,pwd);	//注册
		if(ret==-1){
			sendcomd1("1",socfd);		//发送一条注册失败命令
			goto restart;
		}else if(ret==0){
			sendcomd1("0",socfd);		//发送一条注册成功命令
			char new_user_file[1000]={0};
			sprintf(new_user_file,"%s/%s","/home/zhao/LINUX/FTP文件服务器项目需求/level3/server/user",user);
			mkdir(new_user_file,0777);
			mysql_UserFile_insert("\0",user,"Dir"," ",user,"\0");		//用户文件录入

		goto landing;

		}
	}else if(key==2){
landing:								//注册成功跳转登陆
		printf("新用户登陆\n");
		bzero(user,sizeof(user));
		bzero(pwd,sizeof(pwd));

		recvcomd1(user,socfd);		//接受用户名
		printf("user is %s\n",user);

		ret=mysql_fine_salt(user,salt);		//从mysql提取salt值
		if(ret==-1)
		{
			printf("用户名不存在！\n");
			sendcomd1("3",socfd);		//发送用户不存在
			goto landing;
		}else{
			printf("   user:%s salt:%s\n",user,salt);
			sendcomd1(salt,socfd);		//发送salt值

			recvcomd1(pwd,socfd);		//接受用户所合成密文
			printf("pwd is %s\n",pwd);
		}
		
		ret=mysql_psw_verify(user,pwd);		//密码验证
		if(ret==0){
			printf("用户登陆成功!\n");
			sendcomd1("2",socfd);
			strcpy(USERNAME,user);
		    user_O_F_line_record(user,"ON");				//用户上线记录数据库
			return 0;
		}else if(ret==-1){
			sendcomd1("3",socfd);
			printf("用户登陆失败!\n");
			goto restart;
		}
	}
}


void recvcomd2(char* comd,char* arg,int socfd)
{
	int len1,len2;
	recv_n(socfd,(char*)&len1,sizeof(len1));	//接受命令 或用户名
	recv_n(socfd,comd,len1);
	recv_n(socfd,(char*)&len2,sizeof(len2));	//接受参数 或密码
	recv_n(socfd,arg,len2);
}

void recvcomd1(char* comd,int socfd)
{
	int len1;
	recv_n(socfd,(char*)&len1,sizeof(len1));	//接受命令 或用户名
	recv_n(socfd,comd,len1);
}


void sendcomd1(char* comd ,int socfd)
{
	int len;
	train file;
	bzero(&file,sizeof(file));
	//发送命令
	file.len=strlen(comd);
	strcpy(file.buf,comd);
	send_n(socfd,(char*)&file,4+file.len);
	printf("sendcomd1：%s\n",comd);
}

void sendcomd2(char* comd ,char* arg,int socfd)
{
	int len;
	train file;
	bzero(&file,sizeof(file));
	//发送命令
	file.len=strlen(comd);
	strcpy(file.buf,comd);
	send_n(socfd,(char*)&file,4+file.len);
	printf("命令为：%s\n",comd);
	//发送命令参数
	bzero(&file,sizeof(file));
	file.len=strlen(arg);
	strcpy(file.buf,arg);
	send_n(socfd,(char*)&file,4+file.len);
	printf("参数为：%s\n",arg);
}
