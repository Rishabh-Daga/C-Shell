// #include "input.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
char *ab[100], *bb[100];
char **innp;
void tokee(int tokk , int i  )
{
	char del[100];
	if(tokk==1)
		strcpy(del," ");
	else if(tokk==2 )
		strcpy(del,"<");
	else if(tokk==4)
		strcpy(del,">>");
	else if(tokk==6)
		strcpy(del,">");
	// printf("%s\n",del );
	int sz=0;
	ab[sz]=strtok(innp[i],del); 
	while(ab[sz]!=NULL)
	{
		sz++;
		ab[sz]=strtok(NULL,del);
	}
	for(int i=0;i<sz;i++)
	{
		if(i==0)
		{
			bb[0]=strtok(ab[i]," ");
			int se=0;
			while(bb[se]!=NULL)
			{
				se++;
				bb[se]=strtok(NULL," ");
			}
		}
		else 
			ab[i]=strtok(ab[i]," ");

	}

}
int piping( char *cmd)
{
	char tmp[10000],a[100];
	strcpy(tmp,cmd);
	strcpy(a,"|");
	innp=lsh_split(tmp,a);
	int nopipes=0;
	for(int i=0;innp[i]!=NULL;i++)
	{	
		// printf("%s\n",innp[i] );
		nopipes++;
	}
	nopipes--;
	// printf("%d\n",nopipes );	
	if(!nopipes)
		return 1;
	else
	{
		int fd[2];
		int infd=dup(0),outfd=dup(1);
		int pid,status;
		for(int i=0;i<=nopipes;i++)
		{	
			
			if(!i)
			{
				pipe(fd);
				outfd=dup(1);
				if (dup2(fd[1], 1) == -1)
					fprintf(stderr, "Error: dup2 failed\n");

			}
			else if(i==nopipes)
			{
				close(fd[1]);
				infd = dup(0);
				if (dup2(fd[0], 0) == -1)
					fprintf(stderr, "Error: dup2 failed\n");
				close(fd[0]);
			}
			else
			{	
				close(fd[1]);
				infd = dup(0);
				if (dup2(fd[0], 0) == -1)
					fprintf(stderr, "Error: dup2 failed\n");
				close(fd[0]);
				pipe(fd);
				outfd = dup(1);
				if (dup2(fd[1], 1) == -1)
					fprintf(stderr, "Error: dup2 failed\n");	
			}
			pid=fork();
			if(!pid)
			{
				int len=strlen(innp[i]),toke=1;
				// printf("%d\n",len);
				for(int j=0;j<len;j++)
				{
					if(innp[i][j]=='<')
						toke=2;
					else if(innp[i][j]=='>' && toke==1)
						toke=6;
					else if(innp[i][j]=='>' && toke==6)
						toke=4;
				}
				if(toke!=1)
				{
					// printf("dsasdsa" );
					tokee(toke,i);
					if(toke==2)
						redir(bb,ab);
					else
						redir1(bb,ab,toke);
				}
				else
				{
					// /printf("yoyoyo" );
					char *fu[100];
					int sc=0; 
					fu[sc]=strtok(innp[i]," "); 
					while(fu[sc]!=NULL)
					{
						 // printf("%s\n",fu[sc] );
						sc++;
						fu[sc]=strtok(NULL," ");
					}
					// printf("%s\n",unm );
					 int ex;
				// if(!strcmp(fu[0],"cd") )
				// 	ex=cd(unm,host,fu,cwd);
				// else if(!strcmp(fu[0],"pwd") )
				// 	ex=pwd(unm,host,cwd);
				// else if(!strcmp(fu[0],"ls") )
				// 	ex=ls(unm,host,fu,cwd);
				 if(!strcmp(fu[0],"pinfo"))
				{
					if(fu[1]!=NULL)
						ex=pinfo1(fu);
					else
						ex=pinfo();
				}
				else
	 		 	ex=execvp(fu[0],fu);
	 		 if(ex<0)

					printf("error\n");

				}
				exit(0);
			}
			else if (pid>0)
			{
				waitpid(pid, &status, WUNTRACED);
				dup2(infd,0);
				dup2(outfd,1);
			}
		}
		return 7;
	}

}
