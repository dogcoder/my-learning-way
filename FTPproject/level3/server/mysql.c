#include "head.h"


int mysql_user_register(char* UserName,char* oldpwd)		//用户注册
{

	char Salt[40]={0};
	char Password[200]={0};
	int i,j;

	for(i=0,j=0;i<strlen(oldpwd)&&j!=3;i++)
	{
		if(oldpwd[i]=='$')
			j++;
	}
	strncpy(Salt,oldpwd,i-1);
	strcpy(Password,oldpwd+i);
	printf("salt: %s\nPassword: %s\n",Salt,Password);


	int ret=mysql_confirm_NOsameUser(UserName);		//注册时用户名查重
	if(ret==-1)
		return -1;


	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";
	char query[200]={0};
	sprintf(query,"insert into User(UserName,Salt,Password) values('%s','%s','%s')",UserName,Salt,Password);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
	}
	mysql_close(conn);
	return 0;
}


int mysql_confirm_NOsameUser(char* UserName)		//注册时用户名查重
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";//要访问的数据库名称
	char query[300]={0};
	sprintf(query,"select * from User where UserName='%s'",UserName);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		if((row=mysql_fetch_row(res))==NULL)
		{
			mysql_free_result(res);
			mysql_close(conn);
			return 0;	//用户名不存在
		}else
			mysql_free_result(res);
		mysql_close(conn);
		return -1;	//用户名存在
	}
}


int mysql_fine_salt(char* UserName,char* salt)		//从数据库提取salt值
{

	int ret=mysql_confirm_NOsameUser(UserName);		//用户名是否正确
	if(ret==0)
		return -1;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";//要访问的数据库名称
	char query[300]={0};
	sprintf(query,"select * from User where UserName='%s'",UserName);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(salt,row[2]);
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
}


int mysql_psw_verify(char* UserName,char* psw)		//密码验证
{
	char Salt[20]={0};
	char Password[200]={0};
	char true_psw[200]={0};

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";//要访问的数据库名称
	char query[300]={0};
	sprintf(query,"select * from User where UserName='%s'",UserName);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		if(res)
		{
			row=mysql_fetch_row(res);
			strcpy(Salt,row[2]);
			strcpy(Password,row[3]);
		}
		mysql_free_result(res);
	}
	mysql_close(conn);

	sprintf(true_psw,"%s$%s",Salt,Password);
	//printf("真实密文为：%s\n",true_psw);

	int ret=strcmp(true_psw,psw);
	if(ret==0)
		return 0;
	else
		return -1;
}


void user_O_F_line_record(char* UserName,char* Style)	//用户登陆离线记录
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";
	char query[200]={0};
	sprintf(query,"insert into LandInfo(UserName,Style) values('%s','%s')",UserName,Style);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
	}
	mysql_close(conn);
}

void msql_user_operation(char* UserName,char* Command,char* Arguments)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";
	char query[200]={0};
	sprintf(query,"insert into Operation(UserName,Command,Arguments) values('%s','%s','%s')",UserName,Command,Arguments);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
	}
	mysql_close(conn);
}


int mysql_UserFile_insert(char* NowDir,char* Filename,char* Filetype,char* MD5,char* User,char* AbsRoad)		//用户文件录入
{
	int Precode;
	Precode=mysql_find_KeyCode(NowDir,User);	

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";
	char query[1000]={0};
	sprintf(query,"insert into UserFile(Precode,Filename,Filetype,MD5,User,AbsRoad) values('%d','%s','%s','%s','%s','%s')",Precode,Filename,Filetype,MD5,User,AbsRoad);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
	}
	mysql_close(conn);
	return 0;
}

int mysql_find_KeyCode(char* NowDir,char* User)		//根据当前文件夹及文件夹所属用户确定 寻找code 填入precode
{
	int code=0;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";//要访问的数据库名称
	char query[300]={0};
	sprintf(query,"select * from UserFile where Filename='%s' and User='%s'",NowDir,User);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		if((row=mysql_fetch_row(res))==NULL)
		{
			mysql_free_result(res);
			mysql_close(conn);
			return 0;	//已在根文件夹
		}else{
			sscanf(row[1],"%d",&code);
			printf("father code is :%d\n",code);
			mysql_free_result(res);
			mysql_close(conn);
			return code;	//返回当前文件夹code
		}
	}
}

int mysql_find_MD5(char* myMD5)		//根据客户端所发送MD5码 验证服务端是否存在该文件
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";//要访问的数据库名称
	char query[300]={0};
	sprintf(query,"select * from UserFile where MD5='%s'",myMD5);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		if((row=mysql_fetch_row(res))==NULL)
		{
			mysql_free_result(res);
			mysql_close(conn);
			return 0;	//MD5不存在
		}else{
			mysql_free_result(res);
			mysql_close(conn);
			printf("row is %s\n",row[4]);
			return -1;	//MD5名存在
		}
	}
}

void mysql_find_AbsRoad(char* MD5,char* myroad)		//根据当前文件MD5码，寻找绝对路径用于硬链接
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";//要访问的数据库名称
	char query[300]={0};
	sprintf(query,"select * from UserFile where MD5='%s'",MD5);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		res=mysql_use_result(conn);
		row=mysql_fetch_row(res);

		printf("absolute road is :%s\n",row[6]);
		strcpy(myroad,row[6]);
		mysql_free_result(res);
		mysql_close(conn);
	}
}

int mysql_delete_UserFile(char* Filename,char* User)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="admin";
	char* database="FTP";
	char query[200]={0};
	sprintf(query,"delete from UserFile where Filename='%s' and User='%s'",Filename,User);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}else{
		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}else{
		printf("delete success\n");
	}
	mysql_close(conn);
	return 0;
}
