typedef struct 
{
	int id;
	char name[100];
}Proc;
Proc proc_arr[100];
int proc_cnt=0;
int flag1=0,flag11=0;
char copy[1000];
char name[1000];
int sz=0,ii=0;
char *ff[100];
char *ff1[100],*ff2[100],*ff3[100],*ff4[100];
char **inp;
int globpid;
extern char *unm;
extern char host[2000];
extern char *cwd;