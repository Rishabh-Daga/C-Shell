	int jobs()
{
	if(ff[1]!=NULL)
	{
		printf("error\n");
		return 1;
	}
	int i;
	for(i=1;i<=proc_cnt;i++)
	{
		char adda[100];
		sprintf(adda,"/proc/%d/stat",proc_arr[i].id);
		FILE *fd=fopen(adda,"r");
		if(fd == NULL)
			continue;
		else
		{	
			char a[100][100], c;
			int j=0,il=0;
			while((c=fgetc(fd)) != EOF)
			{
				if(c==' ' || c=='\n')
				{
					a[il][j]='\0';
					il++;
					j=0;
				}
				else
				{
					a[il][j]=c;
					j++;
				}	
			}
			char procst[100];
			// printf("%s\n",a[2]  );
			if(!strcmp(a[2],"R") || !strcmp(a[2],"S"))
				strcpy(procst,"Running");
			// if(!strcmp(a[2],"S"))
			// 	strcpy(procst,"Sleeping");
			if(!strcmp(a[2],"T"))
				strcpy(procst,"Stopped");

			printf("[%d] %s %s %d\n", i,procst, proc_arr[i].name, proc_arr[i].id);
		}
	}
	return 1;
}
int ovk()
{
	// printf("%s %s %s\n",ff[0],ff[1],ff[2] );
		if(ff[1]!=NULL)
	{
		printf("error\n");
		return 1;
	}

	int i,sig=9;
	for(i=1;i<=proc_cnt;i++)
	{
		int k=proc_arr[i].id;
		char adda[100];
		sprintf(adda,"/proc/%d/stat",proc_arr[i].id);
		FILE *fd=fopen(adda,"r");
		if(fd == NULL)
			continue;
		else
		{	
			kill(k,9);
		}
	}
	return 1;
}
void fgg()
{
	pid_t p11 = getpid(),pidnumber;		
		if(ff[1]==NULL)
	{
		printf("error\n");
		return;
	}
else if(ff[2]!=NULL)
{
	printf("error\n");
	return ;
}

		// if(len > 2)
		// {			
		// 	printf("Error : Wrong number of arguments\n");		
		// }
		// if(len == 1)
		// {
		// 	printf("Error : pass arguments\n");
		// }
		int x1;
		x1=atoi(ff[1]);
		if(x1 <= proc_cnt && x1>0)
		{
	   		pidnumber = proc_arr[x1].id;
		    signal(SIGTTOU, SIG_IGN);
		    signal(SIGTTIN, SIG_IGN);
		    tcsetpgrp(0, getpgid(pidnumber));
		    kill(pidnumber, SIGCONT);
		    waitpid(pidnumber, NULL, WUNTRACED);
		    tcsetpgrp(0, p11);
		    signal(SIGTTOU, SIG_DFL);
    		signal(SIGTTIN, SIG_DFL);
		}
		else
			printf("Error : Non existent job number\n");
		return ;
}
void bgg()
{	
	int sum=0,mul=1;
	if(ff[1]==NULL)
	{
		printf("error\n");
		return;
	}

	else if(ff[2]!=NULL)
{
	printf("error\n");
	return ;
}

	for(int j=strlen(ff[1])-1;j>=0;j--)
	{
		sum+=(mul*((int)(ff[1][j])-48));
		mul*=10;
	}
	if(sum>proc_cnt)
	{	
		printf("error" );
		return ;
	}
	else
	{
		char adda[100];
		sprintf(adda,"/proc/%d/stat",proc_arr[sum].id);
		// printf("%s\n",adda );
		FILE *fd=fopen(adda,"r");
		if(fd == NULL)
			{
				printf("error\n");
				return ;
			}
		char a[100][100], c;
		int j=0,il=0;
		while((c=fgetc(fd)) != EOF)
		{
			if(c==' ' || c=='\n')
			{
				a[il][j]='\0';
				il++;
				j=0;
			}
			else
			{
				a[il][j]=c;
				j++;
			}	
		}
		// printf("%s\n",a[2] );
		int ko=strcmp(a[2],"T");
		// printf("%d\n",ko );
		if(ko==0)
		{
			// printf("daa" );
			kill(proc_arr[sum].id,SIGCONT);
		}
	}
	// return 1;
}
int kjobs()
{
	int i,sum1=0,mul=1,sum=0;
	if(ff[1]==NULL || ff[2] ==NULL)
	{
		printf("error\n");
		return 1;
	}
	else if(ff[3]!=NULL)
	{
		printf("error\n");
		return 1;
	}
	for(int j=strlen(ff[2])-1;j>=0;j--)
	{
		sum1+=(mul*((int)(ff[2][j])-48));
		mul*=10;
	}
	mul=1;
	for(int j=strlen(ff[1])-1;j>=0;j--)
	{
		sum+=(mul*((int)(ff[1][j])-48));
		mul*=10;
	}
	if(sum>proc_cnt)
	{	
		printf("error" );
		return 1 ;
	}
	else
	{
		char adda[100];
		sprintf(adda,"/proc/%d/stat",proc_arr[sum].id);
		// printf("%s\n",adda );
		FILE *fd=fopen(adda,"r");
		if(fd == NULL)
			{	printf("error\n");
				return 1;
			}
		else
			kill(proc_arr[sum].id,sum1);
	}
	
	return 1;
}