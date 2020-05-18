int  pinfo1(char *ff[])
{
	char pth[10000];
	int i=0;
	while(ff[1][i]!='\0')
	{
		pth[i]=ff[1][i];
		i++;
	}
	pth[i]='\0';
	char add[1000];
	add[0]='/';
	add[1]='p';
	add[2]='r';
	add[3]='o';
	add[4]='c';
	add[5]='/';
	i=0;
	int yy=6;
	while(pth[i]!='\0')
	{
		add[yy]=pth[i];
		yy++;
		i++;
	}
	add[yy]='/';
	add[1+yy]='s';
	add[yy+2]='t';
	add[yy+3]='a';
	add[yy+4]='t';
	// printf("%s\n",add	 );
	FILE *fd=fopen(add,"r");
	if(fd == NULL)
		{
			printf("error\n");
			return 1;
		}
	char a[100][100];
	char c;
	int j=0;
	i=0;
	while((c=fgetc(fd)) != EOF)
	{
		if(c==' ' || c=='\n')
		{
			a[i][j]='\0';
			i++;
			j=0;
		}
		else
		{
			a[i][j]=c;
			j++;
		}	
	}
	for(int l=0;l<i;l++)
	{
		j=0;
		if(l==0 || l==2 || l==22)
		{
			if(l==0)
				printf("pid--  " );
			if (l==2)
				printf("process state-- " );
			if (l==22)
				printf("memory-- ");
			while(a[l][j]!='\0')
			{
				printf("%c",a[l][j] );
				j++;
			}
			printf("\n");
		}
	}
	char path1[32];
	int cnnt=0;
	i=0;
	while(cnnt!=3)
	{
		path1[i]=add[i];
		if(add[i]=='/')
			cnnt++;
		i++;
	}
	path1[i]='e';
	path1[i+1]='x';
	path1[i+2]='e';

	char buff[1000]="";
	int check = readlink(path1,buff,sizeof(buff));
	printf("Executable path-- ");

	printf("%s\n",buff );
	return 1;
}
int pinfo()
{
	FILE *fd=fopen("/proc/self/stat","r");
	if(fd == NULL)
		printf("haggu\n");
	char a[100][100];
	char c;
	int i=0,j=0;
	while((c=fgetc(fd)) != EOF)
	{
		if(c==' ' || c=='\n')
		{
			a[i][j]='\0';
			i++;
			j=0;
		}
		else
		{
			a[i][j]=c;
			j++;
		}	
	}
	for(int l=0;l<i;l++)
	{
		j=0;
		if(l==0 || l==2 || l==22)
		{
			if(l==0)
				printf("pid--  " );
			if (l==2)
				printf("process state-- " );
			if (l==22)
				printf("memory-- ");
			while(a[l][j]!='\0')
			{
				printf("%c",a[l][j] );
				j++;
			}
			printf("\n");
		}
	}
	char path1[32];
	char buff[1000]="";
	sprintf(path1,"/proc/self/exe");
	int chec=readlink(path1,buff,sizeof(buff));
	printf("Executable path-- ");
	printf("%s\n",buff );
	return 1;
}
