#include "header.h"
extern char **environ;
extern int errno;
map<string,string> expmap;
map<string,string> varmap;

char *env[6];
int last_cmd_status;
unordered_map<string,string> aliasmap;
unordered_map<string,string> appmap;
FILE * hist_file;

string getmap(map<string,string> expmap)
{
	string s="";
	for(auto x : expmap)
	{
		s = s + x.first +"="+x.second+":";
	}
	//cout<<"inside getmap"<<s<<endl;
	return s;
}

void  ALARMhandler(int sig)
{
  signal(SIGALRM, SIG_IGN);          /* ignore this signal       */
  printf("Hello\n");
  signal(SIGALRM, ALARMhandler);     /* reinstall the handler    */
}

void initShell()
{
	hist_file = fopen("history","a");

	if(getenv("varmap")!=NULL)
	{
		cout<<"Exported variables from Parent "<<endl;
		//cout<<getenv("varmap");
		char * s=getenv("varmap");
		char *token = strtok(s, ":"); 
	    while (token != NULL) 
	    { 
	        //printf("%s\n", token); 
	        string tk = string(token);
	        int index = tk.find("=");
	        string ls = tk.substr(0,index);
	        string rs = tk.substr(index+1);
	        cout<<ls<<"="<<rs<<endl;
	        expmap[ls] = rs;
	        token = strtok(NULL, ":"); 
	    }
	    varmap =expmap; 
	}
	

//	if(clearenv()!=0)
//		perror("clearenv() Error");

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
	env[4] = (char *)malloc(sizeof("TERM=xterm-256color"));

	
	strcpy(env[0],user);
	strcpy(env[1],home);
	strcpy(env[2],hostnamebuffer);
	strcpy(env[3],"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin");
	strcpy(env[4],"TERM=xterm-256color");

	//char  *env[5] = {user,home,hostnamebuffer,"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin",(char *)NULL};

	environ = env;
	setenv("DISPLAY",":0",1);
	setenv("DBUS_SESSION_BUS_ADDRESS","unix:path=/run/user/1000/bus",1);
	setenv("XDG_RUNTIME_DIR","/run/user/1000",1);
	
	string ps1 = string(getenv("USER"))+"@"+string(getenv("HOSTNAME"));
	if(getuid()==0)
		ps1 += "# ";
	else
		ps1 += "$ ";

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
       // printf("%s", line);

        if(line[read-1]=='\n')
 	       	line[read-1]=(char)NULL;
 	    if(line[0]=='#')   	
 	    {
 	    	line[read-2]=(char)NULL;
 	    	char *token = strtok(&line[2], ",");
 	    	int no=1; 
 	        string ls,rs;
		    while (token != NULL) 
		    { 
		        //printf("%s\n", token); 
		        
		        if(no==2)
		        {
		        	ls=string(token);
		        }
		        else
		        {
		        	rs=string(token);
		        }
		        token = strtok(NULL, ","); 
		        no++;
		    } 
		    appmap[rs] = ls;
		    cout<<ls<<":"<<rs<<endl;
 	    }
        if(isAliasCommand(line))
		{
			//cout<<"here"<<endl;
			executeAliasCommand(line);
			//cout<<"needs to be handled soon";
		}
        else if(isAssignmentCommand(line))
		{
			executeAssignmentCommand(line);
		}
		
    }

    fclose(fp);
    if (line)
        free(line);
   return;
}

void sigintHandler(int sig_num) 
{ 
  
    signal(SIGINT, sigintHandler); 
    fflush(stdout); 
    fclose(hist_file);
    exit(0);
} 

int main()
{

	signal(SIGINT, sigintHandler); 
	signal(SIGALRM, ALARMhandler);

  
	string input;	
	int file_des;
	cout<<endl<<"--------------------------------------"<<endl;
	cout<<"shellrc file reading ...."<<endl;
	initShell();
	readShellRC();
	cout<<"shellrc file configured"<<endl;
	printWecomeMessage();

	while(1)
	{
		try{

		vector<string> args_vector;
		
		cout<<varmap["PS1"];
		getline(cin,input);
		int i = fprintf(hist_file,"%s\n",input.c_str());
		
		
		input = aliasFilter(input);

		if(input.length()==0)
			continue;
		
		getArguments(input,args_vector);
		int vect_size = args_vector.size();
		char  *args[vect_size+1];

		
		if(isAssignmentCommand(input))
		{
			executeAssignmentCommand(input);
			continue;
		}

		if(pipecommand(args_vector))
		{			
			executePipeCommands(args_vector);
			continue;
		}

		if(isAliasCommand(input))			
		{
			executeAliasCommand(input);
			continue;
		}
		
		if(isExportCommand(input))
		{
			
			executeExportCommand(input);
			continue;
		}

		if(args_vector[0]=="open")
		{
			executeOpenCommand(args_vector);
		}
		if(args_vector[0]=="alarm")
		{
			alarm(stoi(args_vector[1]));
			continue;
		}
		//not working 
// //		if(input=="./shell")
// 		{
// 			cout<<"in functions"<<endl;
// 			executeShellCommand(input);
// 			continue;
// 		}
		
		if(input=="exit")
		{
			exit(0);
		}

		if(getArgumentsArray(args_vector,args)==-1)
			continue;
	
		int child = fork();
		
		if(child==0)
		{
			
			if(strcmp(args[0],"cd")==0)
			{	
				int fg = chdir(args[1]);
				if(fg==-1)
					cout<<"Error unable to open dir"<<endl;
				last_cmd_status = errno;
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
				if(input=="./shell")
				{
					//cout<<"before execution "<<endl;
					setenv("varmap",getmap(expmap).c_str(),1);
					//getmap(expmap);
				}
				if(execvp(args[0], args)==-1)
				{

					cout<<"Error in command with error "<<errno;
				}
				exit(errno);
			}
		}
		else
		{
			//Parent process
			int status;
			wait(&status);
			
			if(WIFEXITED(status))
			{
				//cout<<"childeren exited with "<<WEXITSTATUS(status)<<endl;
				last_cmd_status = WEXITSTATUS(status);
			}
			close(file_des);
		}
	}catch(...)
	{
		cout<<"Some error occured or invalid command";
	}
				//cout<<endl;

	}

	return 0;
}