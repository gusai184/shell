#include "header.h"
extern map<string,string> varmap;
extern char **environ;
char *env[5];


void initShell()
{

	printWecomeMessage();
	
	if(clearenv()!=0)
		perror("clearenv() Error");

	struct passwd pw_entry;
	struct  passwd * pw_entry_ptr;
	int uid = getuid();
	char buf[1024];
	getpwuid_r(uid,&pw_entry,buf,sizeof buf,&pw_entry_ptr);

	char user[256] = "USER=";
	strcat(user,pw_entry_ptr->pw_name);

	char hostname[256],hostnamebuffer[512]="HOSTNAME=";
	gethostname(hostname,256);
	strcat(hostnamebuffer, hostname);
	
	char home[256] = {"HOME="};
	strcat(home,pw_entry_ptr->pw_dir);
	

	env[0] = (char *)malloc(sizeof(user));
	env[1] = (char *)malloc(sizeof(home));
	env[2] = (char *)malloc(sizeof(hostnamebuffer));
	env[3] = (char *)malloc(sizeof("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
	
	strcpy(env[0],user);
	strcpy(env[1],home);
	strcpy(env[2],hostnamebuffer);
	strcpy(env[3],"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	//char  *env[5] = {user,home,hostnamebuffer,"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",(char *)NULL};

	environ = env;

	string ps1 = string(getenv("USER"))+"@"+string(getenv("HOSTNAME"))+"$ ";
	varmap["PS1"] = ps1;

	return;

}

void readShellRC()
{
	
	 FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("shellrc", "r");
    if (fp == NULL)
    {

		cout<<"shellrc not found so not loaded"<<endl;		
		return;
    }
    cout<<"These are variable from shellrc fille : "<<endl;	
    while ((read = getline(&line, &len, fp)) != -1) {
      //  printf("Retrieved line of length %zu:\n", read);
        //printf("%s", line);

        if(line[read-1]=='\n')
        	line[read-1]=(char)NULL;
        if(isAssignmentCommand(line))
		{
			executeAssignmentCommand(line);
		}
		else{
			//cout<<"needs to be handled soon";
		}
    }

    fclose(fp);
    if (line)
        free(line);
   return;
}
