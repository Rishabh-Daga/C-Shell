#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#include <sys/stat.h>
// #include "declarations.h"
void check_back()

{
	int status;
	pid_t wpid;
	// printf("dada");
	while((wpid = waitpid(-1, &status, WNOHANG)) > 0) // Checks for the child processes which have changed there status. 
	{
		 if(WIFEXITED(status))
		{
			for(int j = 1; j <= proc_cnt; j++)
			{
				// printf("%d\n",proc_arr[j].id );
				if(proc_arr[j].id == wpid)
					fprintf(stderr,"%s with pid %d exited normally \n",proc_arr[j].name,proc_arr[j].id);
					
			}
		}
		else if(WIFSIGNALED(status))
		{
			for(int j = 1; j <= proc_cnt; j++)
			{
				// printf("%d\n",proc_arr[j].id );
				if(proc_arr[j].id == wpid)
					fprintf(stderr,"process with pid %d terminated \n",proc_arr[j].id);

					// fprintf(stderr,"%s with pid %d exited normally \n",proc_arr[j].name,proc_arr[j].id);
					
			}

		}
	}
}	 