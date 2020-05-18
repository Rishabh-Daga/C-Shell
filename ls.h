	int  ls(char *unm,char host[],char *ff[],char *cwd)
{
	DIR *mydir;
	struct dirent *myfile;
	struct stat mystat;
	char pth[10000];
	int i=0;

	if(ff[1]!=NULL)
	{
		while(ff[1][i]!='\0' )
		{
			pth[i]=ff[1][i];
			i++;
		}
		pth[i]='\0';	
	}		
	if(ff[1]==NULL)
	{

		pth[0]='.';
		pth[1]='\0';	
		char buf[512];
		mydir = opendir(pth);
		if(mydir==NULL)
		{
			printf("error\n");
			return 1;
		}
		int lsa=0;
		while((myfile = readdir(mydir)) != NULL)
		{

			sprintf(buf, "%s/%s", pth, myfile->d_name);
			stat(buf, &mystat);
			struct passwd *pw =getpwuid(mystat.st_uid);
			struct group *gr =getgrgid(mystat.st_gid);
			if(strcmp(myfile->d_name,".")!=0 && strcmp(myfile->d_name,"..")!=0 && !lsa)
				printf("%s\t", myfile->d_name);
			else if(lsa)
				printf("%s\t", myfile->d_name);

		}
		printf("\n");
		closedir(mydir);
		return 1 ;
	}


	//if(!strcmp(pth,".") || !strcmp(pth,"..") || !strcmp(pth,"~") || !strcmp(pth,"-a"))
	if(strcmp(pth,"-l")!=0  &&  strcmp(pth,"-la")!=0 && strcmp(pth,"-al")!=0 && strcmp(pth,"-l-a") && strcmp(pth,"-a-l"))

	{

		if(!strcmp(pth,"~"))
		{
			i=0;
			while(cwd[i]!='\0')
			{
				pth[i]=cwd[i];
				i++;
			}
			pth[i]='\0';
		}
		int lsa=0;
		// if(!strcmp(pth,"-l"))
		// getcwd(pth,sizeof(pth));
		if(!strcmp(pth,"-a"))
		{
			getcwd(pth,sizeof(pth));
			lsa=1;
		}
		char buf[512];
		mydir = opendir(pth);
				if(mydir==NULL)
		{
			//
			printf("error\n");

			//perror();
			return 1;
		}


		while((myfile = readdir(mydir)) != NULL)
		{

			sprintf(buf, "%s/%s", pth, myfile->d_name);
			stat(buf, &mystat);
			struct passwd *pw =getpwuid(mystat.st_uid);
			struct group *gr =getgrgid(mystat.st_gid);
			if(strcmp(myfile->d_name,".")!=0 && strcmp(myfile->d_name,"..")!=0 && !lsa)
				printf("%s\t", myfile->d_name);
			else if(lsa)
				printf("%s\t", myfile->d_name);

		}
		printf("\n");
		closedir(mydir);
		return 1;
	}
	if(!strcmp(pth,"-l-a") || !strcmp(pth,"-a-l")||!strcmp(pth,"-l") || !strcmp(pth,"-la") || !strcmp(pth,"-al"))
	{

		int lsa=0;
		// printf("%s\n",pth );
		
		// if(!strcmp(pth,"-l"))
			//getcwd(pth,sizeof(pth));
		if(!strcmp(pth,"-l-a") || !strcmp(pth,"-a-l")||!strcmp(pth,"-al") || !strcmp(pth,"-la"))
		// {
			//getcwd(pth,sizeof(pth));
			lsa=1;
		// }
		pth[0]='.';
		pth[1]='\0';
		char buf[512];
		mydir = opendir(pth);
		if(mydir==NULL)
		{
			printf("error\n");

			//perror();
			return 1;
		}

		while((myfile = readdir(mydir)) != NULL)
		{
			sprintf(buf, "%s/%s", pth, myfile->d_name);
			stat(buf, &mystat);
			struct passwd *pw =getpwuid(mystat.st_uid);
			struct group *gr =getgrgid(mystat.st_gid);
			if(strcmp(myfile->d_name,".")!=0 && strcmp(myfile->d_name,"..")!=0 && !lsa)
			{
				// printf("fdfd\n" );
				printf((int) (S_ISDIR(mystat.st_mode)) ? "d" : "-");
				printf((int) (mystat.st_mode & S_IRUSR) ? "r" : "-");
				printf((int) (mystat.st_mode & S_IWUSR) ? "w" : "-");
				printf((int) (mystat.st_mode & S_IXUSR) ? "x" : "-");
				printf((int) (mystat.st_mode & S_IRGRP) ? "r" : "-");
				printf((int) (mystat.st_mode & S_IWGRP) ? "w" : "-");
				printf((int) (mystat.st_mode & S_IXGRP) ? "x" : "-");
				printf((int) (mystat.st_mode & S_IROTH) ? "r" : "-");
				printf((int) (mystat.st_mode & S_IWOTH) ? "w" : "-");
				printf((int) (mystat.st_mode & S_IXOTH) ? "x\t" : "-\t");
				printf("%ld\t",(long)mystat.st_nlink);	
				printf("%s\t",pw->pw_name);
				printf("%s\t",gr->gr_name);
				char *c=ctime(&mystat.st_mtime);
				printf("%zu\t",mystat.st_size);
				char ctm[20000];
				int flg=0,j=0,cnt=0,i=0;
				while(c[i]!='\n')
				{
					if(c[i]==' ')
						flg=1;
					if(flg)
					{
						if(c[i]==':')
						{
							cnt++;
						}
						if(cnt!=2)
						{ctm[j]=c[i];
							j++;
						}
					}
					if(cnt==2)
						break;	
					i++;
				}
				printf("%s\t",ctm);

				// ctime(&mystat.st_mtime));
				//}
				printf("%s\n", myfile->d_name);
		}
		else if(lsa)
		{
			printf((int) (S_ISDIR(mystat.st_mode)) ? "d" : "-");
			printf((int) (mystat.st_mode & S_IRUSR) ? "r" : "-");
			printf((int) (mystat.st_mode & S_IWUSR) ? "w" : "-");
			printf((int) (mystat.st_mode & S_IXUSR) ? "x" : "-");
			printf((int) (mystat.st_mode & S_IRGRP) ? "r" : "-");
			printf((int) (mystat.st_mode & S_IWGRP) ? "w" : "-");
			printf((int) (mystat.st_mode & S_IXGRP) ? "x" : "-");
			printf((int) (mystat.st_mode & S_IROTH) ? "r" : "-");
			printf((int) (mystat.st_mode & S_IWOTH) ? "w" : "-");
			printf((int) (mystat.st_mode & S_IXOTH) ? "x\t" : "-\t");
			printf("%ld\t",(long)mystat.st_nlink);	
			printf("%s\t",pw->pw_name);
			printf("%s\t",gr->gr_name);
			char *c=ctime(&mystat.st_mtime);
			printf("%zu\t",mystat.st_size);

			char ctm[20000];
			int flg=0,j=0,cnt=0,i=0;
			while(c[i]!='\n')
			{
				if(c[i]==' ')
					flg=1;
				if(flg)
				{
					if(c[i]==':')
					{
						cnt++;
					}
					if(cnt!=2)
					{ctm[j]=c[i];
						j++;
					}
				}
				if(cnt==2)
					break;	
				i++;
			}
			printf("%s\t",ctm);
			printf("%s\n", myfile->d_name);
		}
	}
	//printf("\n");
	closedir(mydir);
	return 1;
}

}
