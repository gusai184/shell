#include "header.h"

void printWecomeMessage()
{
	cout<<"\n******************************************"; 
    cout<<"\n\t****Dh@ma SHELL****"; 

    cout<<"\n*******************"
        "***********************\n\n";    
}

void printPrompt()
{
	char hostnamebuffer[256];
	
	string username = string(getenv("USER"));
	string hostname = string(getenv("HOSTNAME"));
	string cwd = string(get_current_dir_name());

	cout<<username<<"@"<<hostname<<":"<<cwd<<"$";
}

void getArguments(string str,vector<string> &args) 
{ 
   string word = ""; 
   for (auto x : str) 
   { 
       if (x == ' ') 
       {     
           args.push_back(word);
           word = ""; 
       } 
       else
       { 
 	          word = word + x; 
       } 
   }  
   args.push_back(word);
} 

int getArgumentsArray(vector<string> args_vector,char  *args[])
{

	int vect_size = args_vector.size();
	
	f(i,0,vect_size-1)
	{
		args[i] = new char[256];

		string s = args_vector[i];
		if(s[0]=='$')
		{
			char * val = getenv(s.substr(1).c_str());
			if(val==NULL)
			{
				return -1;
			}
			strcpy(args[i],val);			
		}
		else if(s == "~")
		{
			strcpy(args[i],getenv("HOME"));
		}
		else
		{
			strcpy(args[i],args_vector[i].c_str());			
		}
	}
	args[vect_size] = NULL;
	return 1;
}