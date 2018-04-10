#include "head.h"
#include "factory.h"
#include "work_que.h"

int cd_comdfunc(char* arg,int socfd,char* mypwd,char* USERNAME,char* NowDir)
{
	if(strcmp(arg,"..")==0){
	}else{
		int ret=mysql_find_KeyCode(arg,USERNAME);		//根据待转移文件夹及文件夹所属用户确定文件夹存在与否
		if(ret==0)
		{
			sendcomd1("该文件夹不存在！",socfd);
			goto end;
		}
	}

	train file;
	bzero(&file,sizeof(file));
	char root[1024];
	getcwd(root,sizeof(root));
	sprintf(root,"%s/%s/%s",root,"user",USERNAME);

	if(strcmp(arg,"..")==0)
	{
		if(strcmp(root,mypwd)==0)
		{
			mypwd="当前已在根目录，无法返回上级目录！";
			file.len=strlen(mypwd);
			strcpy(file.buf,mypwd);
			send_n(socfd,(char*)&file,4+file.len);
			goto end;
		}else{
			printf("接收到返回上级命令\n");
			int j;
			for(int i=0;i<strlen(mypwd);i++)
			{
				if(mypwd[i]=='/')
					j=i;
			}
			mypwd[j]=0;
			file.len=j;
			strcpy(file.buf,mypwd);
			send_n(socfd,(char*)&file,4+file.len);

			//改变NowDir
			for(int i=0;i<strlen(mypwd);i++)
			{
				if(mypwd[i]=='/')
					j=i;
			}
			strcpy(NowDir,&mypwd[j+1]);


			goto end;
		}
	}
	strcpy(NowDir,arg);
	sprintf(mypwd,"%s%c%s",mypwd,'/',arg);
	printf("移动到：./%s\n",arg);
	file.len=strlen(mypwd);
	strcpy(file.buf,mypwd);
	send_n(socfd,(char*)&file,4+file.len);
end:
	return 0;
}


int ls_comdfunc(int socfd,const char* nowpwd)
{
	char stat_pwd[1024]={0};
	printf("准备发送目录\n");
	printf("当前路径为 ：%s\n",nowpwd);
	train file;
	bzero(&file,sizeof(file));
	DIR* dp=opendir(nowpwd);
	if(NULL==dp)
	{
		strcpy(file.buf,"文件夹不存在");
		file.len=strlen(file.buf);
		send_n(socfd,(char*)&file,4+file.len);
		return -1;
	}
	struct dirent *entry;
	struct stat statbuf;
	while((entry=readdir(dp))!=NULL)
	{
		bzero(&statbuf,sizeof(statbuf));
		sprintf(stat_pwd,"%s/%s",nowpwd,entry->d_name);
		int ret=stat(stat_pwd,&statbuf);
		if(ret==-1)
		{
			perror("stat");
		}
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(entry->d_name,".")==0||strcmp(entry->d_name,"..")==0)
				continue;
			sprintf(file.buf,"%s%s",file.buf,"Dir ");
		}else
			sprintf(file.buf,"%s%s",file.buf,"--- ");

		sprintf(file.buf,"%s%s%ld",file.buf,"\t",statbuf.st_size);
		sprintf(file.buf,"%s%s%s",file.buf,"\t",entry->d_name);
		sprintf(file.buf,"%s%s",file.buf,"\n");
	}
	file.len=strlen(file.buf);
	send_n(socfd,(char*)&file,4+file.len);
	closedir(dp);
	printf("发送成功！\n%s\n",file.buf);
	return 0;
}


int mkdir_comdfunc(int socfd,char* name,char* thepwd,char* NowDir,char* User)		//mkdir 处理函数
{
	DIR* pDIR=NULL;
	char buf[1000]={0};
	sprintf(buf,"%s/%s",thepwd,name);

	pDIR=opendir(buf);
	if(pDIR!=NULL)		//文件夹已存在
	{
		sendcomd1("NO",socfd);
		return -1;
	}
	int ret=mkdir(buf,0777);
	if(ret==-1)
	{
		perror("mkdir");
		return -1;
	}
	sendcomd1("OK",socfd);	
	mysql_UserFile_insert(NowDir,name,"Dir"," ",User," ");		//用户文件夹录入
	return 0;
}
