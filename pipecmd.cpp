#include "header.h"

bool pipecommand(vector<string> & cmd)
{
	
	f(i,0,cmd.size()-1) 
	{
		string token = cmd[i];
		
		if(token == "|")
			return true;
	}
	return false;
}

void separatePipe(vector<string> source,vector<string> &desti)
{
	string s = "";
	f(i,0,source.size()-1)
	{
		string token = source[i];
		if(token=="|" && s!="")
		{
			desti.push_back(s.substr(0,s.length()-1));			
			s = "";
		}
		else
		{
			s = s + token + " ";
		}
	}
	desti.push_back(s.substr(0,s.length()-1));
	
}
void getArgsFromString(string s, char *args[])
{
   string word = ""; 
   int i=0;
   for (auto x : s) 
   { 
       if (x == ' ') 
       {   
       		if(word!=" " && word!="")
       		{
       			args[i] = new char[256];
       			strcpy(args[i++],word.c_str());	
       			//cout<<args[i-1]<<endl;
       		}
           word = ""; 
       } 
       else
       { 
 	          word = word + x; 
       } 
   }  
   args[i] = new char[256];
   strcpy(args[i++],word.c_str());
   //cout<<args[i-1];
   args[i] = NULL;
}

void executePipeCommands(vector<string> cmd)
{
	
	vector<string> vectcmd;
	separatePipe(cmd,vectcmd);
	for(auto x:vectcmd)
	{
		cout<<x<<":"<<endl;
	}

	int fd[2];	
	if(pipe(fd)<0)
	{
		cout<<"error in pipe";
		return;
	}

	f(i,0,vectcmd.size()-1)
	{
		char *args[128];
		getArgsFromString(vectcmd[i],args);
	
		int pid = fork();

		if(pid==0)
		{
			if(i!=0)
				dup2(fd[0],0);
			if(i!=(vectcmd.size()-1))
				dup2(fd[1],1);
			close(fd[0]);
			close(fd[1]);			
			///write(1,"command ",strlen("command"));
			//write(1,vectcmd[i].c_str(),vectcmd[i].size());
			execvp(args[0],args);
		}
		else{
			//close(fd[0]);
			//close(fd[1]);
			//wait(NULL);		
		}
	}

	close(fd[0]);
	close(fd[1]);
	while(wait(NULL)>0);
}

