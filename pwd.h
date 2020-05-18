int  pwd(char *unm,char host[],char *cwd)

{
	char cwd1[100005];
	if(getcwd(cwd1,sizeof(cwd1))!=NULL)
		printf("%s\n",cwd1);
	else
		perror("getcwd() error");
	return 1;
}
int  echo(char *unm,char host[],char *ff[],char *cwd)
{

	printf("%s\n",ff[1]);
	return 1;
}
