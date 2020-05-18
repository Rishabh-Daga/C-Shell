int setenvfunction(char *ff[])
    {
	if(ff[1]==NULL || ff[3]!=NULL)   
        printf("Invalid argument \n");
    if (ff[2] == NULL)
        ff[2] = " ";
	if (setenv(ff[1],ff[2],1) != 0)    
        perror("shell ");
	return 1;	
}
int unsetenvfunction(char *ff[])
    {
	   if(ff[1]==NULL || ff[2]!=NULL)  
            printf("Invalid argument \n");
        if (unsetenv(ff[1]) != 0) 
            perror("shell");
	   return 1;
    }
int getenvfunction(char *ff[])
    {
        if(getenv(ff[1])==0)
            fprintf(stderr,"Invalid format\n");
        else
            printf("%s\n",getenv(ff[1]));
    }
