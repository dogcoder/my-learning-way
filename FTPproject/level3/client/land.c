#include "head.h"
//注册 及登陆
int cli_land(int socfd)
{

	int i=0;
	int key=0;
	int len;
	char buf[20];
	char *pass=NULL,*pass1=NULL;
	char us_name[50];
	char us_psw[500];
	char us_psw1[50];
restart:
	bzero(&key,sizeof(key));
	bzero(us_name,sizeof(us_name));
	bzero(us_psw,sizeof(us_psw));
	bzero(us_psw1,sizeof(us_psw1));
	bzero(buf,sizeof(buf));

	system("clear");

	printf("请选择新用户注册 或登陆\n");
	printf("    注册请按1    登陆请按2\n");

	scanf("%d",&key);
	send(socfd,&key,4,0);
	if(key==1){							//注册新用户
		system("clear");

		printf("请输入新用户账户：");
		scanf("%s",us_name);
retry:
		printf("\n请输入新用户密码：");
		scanf("%s",us_psw);
		printf("\n请再次输入新用户密码：");
		scanf("%s",us_psw1);

		if(strcmp(us_psw,us_psw1))
		{
			printf("两次密码输入错误！请重新输入");
			goto retry;
		}
		salt_password(us_psw);
		sendcomd(us_name,us_psw,socfd);

		system("clear");
		recv_n(socfd,(char*)&len,sizeof(len));
		recv_n(socfd,buf,len);

		if(!strcmp(buf,"0")){
			printf("注册成功\n");
				goto landing;
		}else if(!strcmp(buf,"1")){
			printf("用户名已经存在，请重新注册\n");
			sleep(3);
			goto restart;
		}

	}else if(key==2){					//用户登陆
landing:

		system("clear");
		printf("请输入用户账户：");
		scanf("%s",us_name);
		sendcomd1(us_name,socfd);	//发送用户名，等待接受salt值

		bzero(buf,sizeof(buf));	
	    recvcomd1(buf,socfd);		//接受salt
		
		if(strcmp(buf,"3")==0){
			printf("用户不存在\n");
			sleep(3);
			goto landing;
		}

		printf("salt : %s\n",buf);

		//printf("\n请输入用户密码：");
		pass=getpass("请输入新用户密码：");
		strcpy(us_psw,pass);
		//scanf("%s",us_psw);
		salt_merge(buf,us_psw);		//用户端合成密文
		sendcomd1(us_psw,socfd);	//发送密文等待验证信息
	
		bzero(buf,sizeof(buf));
	    recvcomd1(buf,socfd);		//接受登陆反馈信息
		if(!strcmp(buf,"2")){
			printf("登陆成功，正在跳转......\n");
				return 0;
		}else if(!strcmp(buf,"3")){
			printf("登陆失败，密码错误 还有%d次机会\n",2-i++);
			sleep(2);
			if(i==3)
				return -1;
			goto restart;
		}


	}else{
		printf("命令错误，请重新输入！\n");
		fflush(stdin);
		fflush(stdout);
		sleep(2);
		goto restart;
	}
}
