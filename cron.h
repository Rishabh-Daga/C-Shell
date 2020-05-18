void cronjob(char *ff[] )
{
	int l=0;
	int r=0;
	int i=0;
	int p=0;
	char* comd[10];
	for(int z=0;z<10;z++)
		comd[z]=(char*)malloc(100*sizeof(char));
	while(strcmp(ff[r],"-t")!=0)
		r++;
	while(strcmp(ff[l],"-c")!=0)
		l++;
	l++;
	r++;
	i=l;
	while(i!=r-1)
	{
		strcpy(comd[p],ff[i]);
		// printf("%s\n",comd[p] );
		i++;
		p++;
	}
	i=0;
	comd[p]=NULL;
	int total=atoi(ff[r+2]);
	int interval=atoi(ff[r]);
	while(total!=0 && total>0)
	{
		int pid=fork();
		if(!pid)
		{
			setpgid(0,0);

			sleep(interval);
			int x;
			if(!strcmp(comd[0],"pinfo"))
				pinfo();
			else
			x=execvp(comd[0],comd);
		if(x<0)
			printf("error\n" );
			exit(0);
		}
		else if(pid>0) 
		{	int status;
			waitpid(pid,&status,WUNTRACED);
			total-=interval;
		}
	}
}