#include "head.h"
#include "factory.h"
#include "work_que.h"

int cd_comdfunc(char* arg,int socfd,char* mypwd)
{
	train file;
	bzero(&file,sizeof(file));
	char root[1024];
	getcwd(root,sizeof(root));

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
			goto end;
		}
	}
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
	char root[1024];
	getcwd(root,sizeof(root));
	chdir(nowpwd);
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
		printf("a ");
	//	bzero(&statbuf,sizeof(statbuf));
		int ret=stat(entry->d_name,&statbuf);
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
		chdir(root);
		file.len=strlen(file.buf);
		send_n(socfd,(char*)&file,4+file.len);
		closedir(dp);
		printf("发送成功！\n%s\n",file.buf);
		return 0;
}
