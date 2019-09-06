#include "header.h"
extern unordered_map<string,string> aliasmap;
extern map<string,string> varmap;
extern map<string,string> expmap;
extern int last_cmd_status;

void printWecomeMessage()
{
	cout<<"\n******************************************"; 
    cout<<"\n\t****Dh@ma SHELL****"; 

    cout<<"\n*******************"
        "***********************\n\n";    
}


void getArguments(string str,vector<string> &args) 
{ 
   string word = ""; 
   for (auto x : str) 
   { 
       if (x == ' ') 
       {   
       		if(word!=" ")
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
			string str = checkForVar(s);
			strcpy(args[i],str.c_str());			
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


bool isAssignmentCommand(string s)
{
	int fg=0;
	for(auto x : s)
	{
		if(x==' ')
			return false;
		if(x=='=')
			fg=1;
	}
	return fg==1;
}

string checkForVar(string s)
{	
	
	if(s=="$")
		return s;
	
	if(s=="~")
	{
		return string(getenv("HOME"));
	}

	if(s=="$$")
	{
		int id = getpid();
		return to_string(id);
	}

	if(s=="$?")
	{	
		return to_string(last_cmd_status);
	}

	if(s[0]!='$')
		return s;

	string s1 = s.substr(1);
	char *envar = getenv(s1.c_str());
	if(envar != NULL)
		return string(envar);
	if(varmap.find(s1)!=varmap.end())
		return varmap[s1];
	return "";
}

bool executeAssignmentCommand(string s)
{
	 for(auto x : s)
	{
		if(x==' ')
		{
			cout<<"Invalid = command"<<endl;
			return false;
		}
	}
	int index = s.find("=");
	string name = s.substr(0,index);
	string value = s.substr(index+1);
	cout<<"variable : "<<name<<"="<<checkForVar(value)<<endl;
	//enviornment var exist
	if(getenv(name.c_str()) != NULL)
		setenv(name.c_str(),checkForVar(value).c_str(),1);
	else
		varmap[name] = checkForVar(value);
	
	
	
	return true;

}