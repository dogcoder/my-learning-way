#include "head.h"

void salt_password(char* psw)			//合成密文
{
	char *str="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int lon=strlen(str);
	int num=10;
	char salt[50];
	char true_salt[50];
	bzero(true_salt,50);
	strcpy(true_salt,"$6$\0");
	bzero(salt,sizeof(salt));
	srand((unsigned int)time((time_t*)NULL));

	for(int i=0;i<num;i++)
		sprintf(salt,"%s%c",salt,str[(rand()%lon)]);


	strcat(true_salt,salt);
	printf("salt=%s\n",true_salt);
	strcpy(psw,crypt(psw,true_salt));
	printf("密文是:%s\n",psw);
}


void salt_merge(char* salt,char* psw)		//合成密文
{
	strcpy(psw,crypt(psw,salt));
}

int cal_MD5(char* FileName,unsigned char* myMD5)  
{  
	MD5_CTX ctx;  
	unsigned char outmd[16];  
	char buffer[1024];
	char buf[33]={0};
	char tmp[3]={0};
	int len=0;  
	int i;  
	FILE * fp=NULL;  
	memset(outmd,0,sizeof(outmd));  
	memset(buffer,0,sizeof(buffer));  
	fp=fopen(FileName,"rb");  
	if(fp==NULL)  
	{  
		printf("Can't open file\n");  
		return 0;  
	}  

	MD5_Init(&ctx);  
	while((len=fread(buffer,1,1024,fp))>0)  
	{  
		MD5_Update(&ctx,buffer,len);  
		memset(buffer,0,sizeof(buffer));  
	}  
	MD5_Final(outmd,&ctx);  

	for(i=0;i<16;i<i++)  
	{  
		sprintf(tmp,"%02X",outmd[i]);
		strcat(buf,tmp);
	}

	strcpy(myMD5,buf);
	return 0;  
}  
