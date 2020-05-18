int cd(char *unm,char host[],char *ff[],char *cwd)
{	
	//printf("%s\n",cwd );
	int y;
	if(ff[1]==NULL)
	{
		chdir(cwd);
		return 1;
	}
	y=strcmp(ff[1],"..");
	if(!y)
	{
		chdir("..");
		return 1;

	}
	y=strcmp(ff[1],".");
	if(!y)
	{
		char cwd1[100005];
		return 1;

	}
	y=strcmp(ff[1],"~");
	if(!y)
	{
		chdir(cwd);
		return 1;
	}
	int n,m,r;
	n=strcmp(ff[1],"..");
	m=strcmp(ff[1],".");
	r=strcmp(ff[1],"~");
	if(n!=0 && m!=0 && r!=0)
	{
		char pth[10000];
		int itr=0;
		// if()
		if(strcmp(ff[1],"~")>=0)
		{
			while(cwd[itr]!='\0')
			{
				pth[itr]=cwd[itr];
				itr++;
			}
			int i=1;
			while(ff[1][i]!='\0')
			{
				pth[itr]=ff[1][i];
				itr++;
				i++;
			}
			//printf("%s\n",pth );
			int x=chdir(pth);
			if(x<0)
			{
				perror("error\n");
			}
			return 1;
		}
		else
		{
			int x=chdir(ff[1]);
			if(x<0)
			{
				perror("error\n");
			}
			return 1;
		}


	}

	//printf("\n");
}
