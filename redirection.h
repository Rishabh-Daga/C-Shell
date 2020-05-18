
   #include<sys/types.h>
   #include <sys/stat.h>
   #include <fcntl.h>
     #include <unistd.h>

void redir(char *ff1[],char *ff[])
{
	pid_t pid=fork();
	int status;
	if(pid<0)
		printf("error" );
	
	else if(!pid)
	{
		int fd;
		 fd=open(ff[1],O_RDONLY);
		 // printf("%d %s\n",fd,ff[1]);
		 if(fd<0)
		 {	printf("error\n" );
		return ;
		}
		 dup2(fd,0);
		 		 int ex;
				// if(!strcmp(ff1[0],"cd") )
				// 	ex=cd(uunm,hostt,ff1,cwdd);
				// else if(!strcmp(ff1[0],"pwd") )
				// 	ex=pwd(uunm,hostt,cwdd);
				// else if(!strcmp(ff1[0],"ls") )
				// 	ex=ls(uunm,hostt,ff1,cwdd);
				if(!strcmp(ff1[0],"pinfo"))
				{
					if(ff1[1]!=NULL)
						ex=pinfo1(ff1);
					else
						ex=pinfo();
				}
				else
	 		 	ex=execvp(ff1[0],ff1);
		 if(ex<0)
		 {
		 	printf("error" );
		 	exit(0);
		 }

		 close(fd);
		  exit(0);
	}
	else
	{	waitpid(pid,&status,0);
		return; }

}
void redir1(char *ff1[],char *ff[],int tokk)
{
	pid_t pid=fork();
	int status;
	if(pid<0)
		printf("error" );
	
	else if(!pid)
	{
		int fd;
		 // fd=open(ff[1],O_RDWR|O_CREAT,0777);
		 // printf("%d %s\n",fd,ff[1]);
		if(tokk==6)
		 fd=open(ff[1],O_RDWR|O_CREAT|O_TRUNC,0777);
		else
		 fd=open(ff[1],O_RDWR|O_CREAT|O_APPEND,0777);
		 if(fd<0)
		 {	
		 	printf("error\n" );
			return ;
		}
		 dup2(fd,1);
		 		 		 int ex;
				// if(!strcmp(ff1[0],"cd") )
				// 	ex=cd(uunm,hostt,ff1,cwdd);
				// else if(!strcmp(ff1[0],"pwd") )
				// 	ex=pwd(uunm,hostt,cwdd);
				// else if(!strcmp(ff1[0],"ls") )
				// 	ex=ls(uunm,hostt,ff1,cwdd);
				 if(!strcmp(ff1[0],"pinfo"))
				{
					// printf("dasda\n");
					if(ff1[1]!=NULL)
						ex=pinfo1(ff1);
					else
						ex=pinfo();
				}
				else
	 		 	ex=execvp(ff1[0],ff1);


		 if(ex<0)
		 {
		 	printf("error" );
		 	exit(0);
		 }
		 close(fd);
		  exit(0);
	}
	else
	{	waitpid(pid,&status,0);
		return; }

}
void redir2(char *ff1[],char *ff3[],char *ff4[],int tokk)
{
	pid_t pid=fork();
	int status;
	if(pid<0)
		printf("error" );
	
	else if(!pid)
	{
		int fd,fd1;
		 if(tokk==3)
		 fd=open(ff4[0],O_RDWR|O_CREAT|O_TRUNC,0777);
		else
		 fd=open(ff4[0],O_RDWR|O_CREAT|O_APPEND,0777);

		 fd1=open(ff3[0],O_RDWR);
		 
		 // printf("%d %s\n",fd,ff[1]);
		 if(fd<0)
		 {	printf("error\n" );
		return ;
		} 
		 dup2(fd1,0);
		 dup2(fd,1);
		 		 		 		 int ex;
				// if(!strcmp(ff1[0],"cd") )
				// 	ex=cd(uunm,hostt,ff1,cwdd);
				// else if(!strcmp(ff1[0],"pwd") )
				// 	ex=pwd(uunm,hostt,cwdd);
				// else if(!strcmp(ff1[0],"ls") )
				// 	ex=ls(uunm,hostt,ff1,cwdd);
				if(!strcmp(ff1[0],"pinfo"))
				{
					if(ff1[1]!=NULL)
						ex=pinfo1(ff1);
					else
						ex=pinfo();
				}
				else
	 		 	ex=execvp(ff1[0],ff1);


		 if(ex<0)
		 {
		 	printf("error" );
		 	exit(0);
		 }
		 close(fd);
		  exit(0);
	}
	else
	{	waitpid(pid,&status,0);
		return; }

}
