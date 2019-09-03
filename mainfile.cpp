#include "header.h"
extern char **environ;
int main()
{
	string input;	
	int file_des;
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
	
	char  *env[5] = {user,home,hostnamebuffer,"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",(char *)NULL};
	environ = env;

	while(1)
	{
		vector<string> args_vector;
		printPrompt();
		getline(cin,input);

		if(input.length()==0)
			continue;

		getArguments(input,args_vector);
		int vect_size = args_vector.size();
		char  *args[vect_size+1];
		
		if(getArgumentsArray(args_vector,args)==-1)
			continue;

		int child = fork();
		
		if(child==0)
		{
			if(strcmp(args[0],"cd")==0)
			{	
				int fg = chdir(args[1]);
				if(fg==-1)
					cout<<"Error unable to open dir";
			}
			else		
			{

				if(vect_size > 2  && (strcmp(args[2],">")==0 || strcmp(args[2],">>") == 0))
				{
				
				   
					if(strcmp(args[2],">")==0)
						file_des = open(args[3],O_WRONLY | O_CREAT,S_IRWXU);
					else if(strcmp(args[2],">>") == 0)
					{						
						file_des = open(args[3],O_APPEND | O_WRONLY,S_IRWXU);
						if(file_des<0)
						{
							file_des = open(args[3],O_WRONLY | O_CREAT,S_IRWXU);
						}						
					}
					else
					{
						cout<<"errro";
						continue;
					}
					if(file_des<0)
					{
						cout<<"Error while openting file"<<endl;
						continue;
					}
					dup2(file_des,1);
					args[2] = (char *)NULL;
					args[3] = (char *)NULL;
					execvp(args[0],args);
				}
				if(execvp(args[0], args)==-1)
					cout<<"Error in command";
			}
		}
		else
		{
			wait(NULL);
			close(file_des);
		}

		cout<<endl;

	}

	return 0;
}