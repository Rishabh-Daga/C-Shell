#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/socket.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h> 
#include "input.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "redirection.h"
#include "pipes.h"
#include "global.h"
#include "jobs.h"
#include "env.h"
#include "bgcheck.h"
#include "cron.h"
#define clear() printf("\033[H\033[J") 

void tok(int tokk)
{
	char del[100];
	if(tokk==1)
		strcpy(del," ");
	else if(tokk==2 || tokk==3 || tokk==5)
		strcpy(del,"<");
	else if(tokk==4)
		strcpy(del,">>");
	else if(tokk==6)
		strcpy(del,">");
	ff[0]=strtok(inp[ii],del); 
	sz=0;
	while(ff[sz]!=NULL)
	{
		sz++;
		ff[sz]=strtok(NULL,del);
	}

}
void prompt()
{
	char *unm1= getlogin();
	char host1[2000];
	int hostii;
	hostii=gethostname(host1,sizeof(host1));
	char *cwdd=(char *)malloc(1000);
	cwdd=realpath(copy,NULL);
	for(int i=strlen(cwdd)-1;i>=0;i--)
	{
		if(cwdd[i]=='/')
		{
			cwdd[i]='\0';
			break;
		}
	}

	char cwd11[1000];

	if(getcwd(cwd11,sizeof(cwd11))!=NULL)
	{	
		if(strcmp(cwd11,cwdd)>=0)
		{
			char cwd2[10000];
			cwd2[0]='~';
			int val=1;
			for(int i=strlen(cwdd);i<strlen(cwd11);i++)
				cwd2[val++]=cwd11[i];
			cwd2[val]='\0';
			printf("<%s@%s:%s>",unm1,host1,cwd2);
		}
		else
			printf("<%s@%s:%s>",unm1,host1,cwd11);

	}
	else
		perror("getcwd() error");
	fflush(stdout);
	return ;
}

void handler(int sig)
{
	pid_t pid;
	int status;
	char *exit=(char *)malloc(10000);
	char *exit_status =(char *)malloc(10000);
	pid =waitpid(0,&status,WNOHANG);
	// printf("caleed\n" );
	sprintf(exit,"\n%s with pid %d exited.\n",name,pid);
	if (WIFEXITED(status))
	{
		int ret=WEXITSTATUS(status);
		// printf("%d",ret);
		if(ret==0)
			sprintf(exit_status,"normally\n");
		else
			sprintf(exit_status,"abnormally\n");

	}
	else if(WIFSIGNALED(status))
	{
		int ret=WEXITSTATUS(status);
		if(ret==0)
			sprintf(exit_status,"normally\n");
		else
			sprintf(exit_status,"abnormally\n");

	}
	if (pid>0)
	{
		write(2,exit,strlen(exit));
		write(2,exit_status,strlen(exit_status));
	prompt();
	fflush(stdout);

	}
	free(exit);
	free(exit_status);
	return ;
}
void fg(char* ff[]) 
{ 
	// Forking a child 
	pid_t pid = fork();  
	int status;
	// printf("%s",ff[1] );
	if (pid <0) 
	{ 
		printf("\nFailed forking child.."); 
		return; 
	}
	else if (!pid) 
	{ 
		if (execvp(ff[0], ff) < 0) 
		{ 
			printf("\nCould not execute command.."); 
		} 
		exit(0); 
	}
	else 
	{ 
		globpid=pid;
		// int statuss;
	
		waitpid(pid,&status,WUNTRACED);
		return; 
	} 
}
void bg(char* ff[]) 
{ 
	// Forking a child 
	pid_t pid = fork();  
	if (pid <0) 
	{ 
		printf("\nFailed forking child.."); 
		return ; 
	} 
	else if (!pid)
	{ 
		// if(!strcmp(ff[0],"vim"))
		setpgid(0,0);	
		if (execvp(ff[0], ff) < 0) 
			printf("\nCould not execute command."); 
		exit(0); 
	} 
	else {
		// globpid=pid;
		proc_arr[proc_cnt].id=pid;
		int k=1,jj=1;
		strcpy(proc_arr[proc_cnt].name,ff[0]);
		while(ff[jj]!=NULL)
		{
			strcat(proc_arr[proc_cnt].name," ");
			strcat(proc_arr[proc_cnt].name,ff[jj]);
			jj++;
		}
		strcpy(name,ff[0]);
	 	// signal(SIGCHLD,handler);
	} 
} 
void hand1(int sig)
{
	// printf("\n");
	// return ;
	 pid_t process = globpid;
    if (process !=0 && process!=-1) 
    {
        kill(process, SIGINT);
        printf("\n");
        fflush(stdout);
    } 
    else 
    {
        printf("\n");
        // print_dirname(size);
        prompt();
        fflush(stdout);
    }
}
void stopSignal(int sig_num)
{
	if(globpid!=0 && globpid!=-1)
	{
		int flag = 1;
		for(int i=1;i<=proc_cnt;i++)
		{
			if(proc_arr[i].id == globpid)
			{
				flag = 0;
				printf("\n%s\t\t%s\t[%d]\n","Stopped",proc_arr[i].name,proc_arr[i].id);
				break;
			}
		}
		if(flag)
		{
			proc_cnt++;
			proc_arr[proc_cnt].id = globpid;
			// proc[num_background_proc].state = 1;
			strcpy(proc_arr[proc_cnt].name,ff[0]);
			// back_proc[num_background_proc].jobid = num_background_proc;
				printf("\n%s\t\t%s\t[%d]\n","Stopped",proc_arr[proc_cnt].name,proc_arr[proc_cnt].id);

			// printf("\n%s\t\t%s\t[%d]\n","Stopped",back_proc[num_background_proc].command,back_proc[num_background_proc].pid);

			// num_background_proc++;/
		}

		int temp = globpid;
		kill(globpid, sig_num);
		globpid = 0;
		printf("\n");
		fflush(stdout);
	}
	else
	{
		printf("\n");
		prompt();
		fflush(stdout);
	}
}
int main(int argc, char const *argv[])
{
	clear();
		check_back();
		signal(SIGTSTP,stopSignal);

	signal(SIGINT,hand1);
	char *unm= getlogin();
	char host[2000];
	int hosti;
	hosti=gethostname(host,sizeof(host));

	if(hosti==-1)
	{
		perror("gethostname");
		exit(1);
	}
	char *cwd=(char *)malloc(1000);
	cwd=realpath(argv[0],NULL);	
	strcpy(copy,argv[0]);
	//printf("%s\n",copy );
	for(int i=strlen(cwd)-1;i>=0;i--)
	{
		if(cwd[i]=='/')
		{
			cwd[i]='\0';
			break;
		}
		//prompt();
	}

	while(1)
	{
		// signal(SIGINT,hand1);
		check_back();
		char cwd11[1000];
		if(getcwd(cwd11,sizeof(cwd11))!=NULL)
		{	
			if(strcmp(cwd11,cwd)>=0)
			{
				char cwd2[10000];
				cwd2[0]='~';
				int val=1;
				for(int i=strlen(cwd);i<strlen(cwd11);i++)
					cwd2[val++]=cwd11[i];
				cwd2[val]='\0';
				printf("<%s@%s:%s>",unm,host,cwd2);
			}
			else
				printf("<%s@%s:%s>",unm,host,cwd11);
		}
		else
			perror("getcwd() error");
		int flag=0;
		char *line=lsh_read_line();
		inp=lsh_split_line1(line);
		ii=0;
		while(inp[ii]!=NULL )
		{
			flag=0,flag1=0,flag11=1;
			flag11= piping(inp[ii]);
		check_back();

			if(flag11!=7)
			{
				for(long unsigned int i=0;i<strlen(line);i++)
				{
					if(line[i]=='<')
						flag11=2;
					else if(line[i]=='>' && flag11==2)
						flag11=3;
					else if(line[i]=='>' && flag11==1)
						flag11=6;
					else if(line[i]=='>' && flag11==6 && i>0)
						flag11=4;
					else if(line[i]=='>' && flag11==3 && i>0)
						flag11=5;

				}
				tok(flag11);
				if(!strcmp(ff[sz-1],"&") )
					flag=1;
				int xx;
				xx=strcmp(ff[0],"cronjob");
				if(!xx && flag11==1)
					{
						cronjob(ff);
						flag1=1;
					}

				xx=strcmp(ff[0],"setenv");
				if(!xx && flag11==1)
					flag1=setenvfunction(ff);
				xx=strcmp(ff[0],"unsetenv");
				if(!xx && flag11==1)
					flag1=unsetenvfunction(ff);
				xx=strcmp(ff[0],"getenv");
				if(!xx && flag11==1)
					flag1=getenvfunction(ff);

				xx=strcmp(ff[0],"overkill");
				if(!xx && flag11==1)
					flag1=ovk();
				xx=strcmp(ff[0],"bg");
				if(!xx && flag11==1)
				{
					bgg();
					flag1=1;
				}
				xx=strcmp(ff[0],"fg");
				if(!xx && flag11==1)
				{
					fgg();
					flag1=1;
				}

				xx=strcmp(ff[0],"jobs");
				if(!xx && flag11==1)
					flag1=jobs();
				xx=strcmp(ff[0],"kjob");
				if(!xx && flag11==1)
					flag1=kjobs();

				xx=strcmp(ff[0],"cd");
				if(!xx && flag11==1 )
				{
					if(flag)
						ff[sz-1]='\0';
					flag=0;
					flag1=cd(unm,host,ff,cwd);
				}
				xx=strcmp(ff[0],"pwd");
				if(!xx && flag11==1 )
				{					
					if(flag)

						ff[sz-1]='\0';
					flag=0;

					flag1=pwd(unm,host,cwd);
				}	
				xx=strcmp(ff[0],"echo");
				if(!xx && flag11==1 )
				{
					flag=0;
					flag1=echo(unm,host,ff,cwd);
				}
					if(strcmp(ff[0],"quit")==0 && flag11==1)
					{	flag1=1;
						exit(1);
					}

				xx=strcmp(ff[0],"ls");
				if(!xx && flag11==1)
				{
					if(flag)
						ff[sz-1]='\0';
					flag=0;
					flag1=ls(unm,host,ff,cwd);
				}
				xx=strcmp(ff[0],"pinfo");
				if(!xx  && flag11==1)
				{
					if(flag)
						ff[sz-1]='\0';
					flag=0;

					if(ff[1]!=NULL)
						flag1=pinfo1(ff);
					else
						flag1=pinfo();
				}
				if(!flag1 && !flag && strcmp(ff[0],"exit"))
				{
					flag1=flag11;

					if(flag1==1)
					{
						ff[sz]='\0';
						fg(ff);
					}
					else if(flag1==2 || flag1==6 || flag1==4) 
					{
						for(int i=0;i<sz;i++)
						{
							if(i==0)
							{
								ff1[0]=strtok(ff[i]," ");
								int se=0;
								while(ff1[se]!=NULL)
								{
									se++;
									ff1[se]=strtok(NULL," ");
								}
							}
							else 
								ff[i]=strtok(ff[i]," ");

						}
						if(flag1==2)
							redir(ff1,ff);
						else
							redir1(ff1,ff,flag1);	
					}
					else if(flag1==3 || flag1==5)
					{
						for(int i=0;i<sz;i++)
						{
							if(i==0)
							{
								ff1[0]=strtok(ff[i]," ");
								int se=0;
								while(ff1[se]!=NULL)
								{
									se++;
									ff1[se]=strtok(NULL," ");
								}
							}
							else if(i==1)
							{
								char del[100];
								if(flag1==3)
									strcpy(del,">>");
								else
									strcpy(del,">");
								ff2[0]=strtok(ff[1],del); 
								int szz=0;
								while(ff2[szz]!=NULL)
								{
									szz++;
									ff2[szz]=strtok(NULL,del);
								}
								ff3[0]=strtok(ff2[0]," ");
								int se=0;
								while(ff3[se]!=NULL)
								{
									se++;
									ff3[se]=strtok(NULL," ");
								}
								ff4[0]=strtok(ff2[1]," ");
								se=0;
								while(ff4[se]!=NULL)
								{
									se++;
									ff4[se]=strtok(NULL," ");
								}
							}

						}
						redir2(ff1,ff3,ff4,flag1);
					}
				}
				if (flag )
				{
					ff[sz-1]='\0';
					proc_cnt++;
					bg(ff);
					check_back();
				}
		check_back();

			}
			ii++;		
		}
	}
}
