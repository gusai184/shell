#include "header.h"
extern map<string,string> varmap;
extern map<string,string> expmap;



bool isExportCommand(string input)
{
	if(input.substr(0,6)=="export")
		return true;
	return false;
}

void executeExportCommand(string input)
{
	string variable = input.substr(7);
	//cout<<variable<<"is var"<<endl;
	if(varmap.find(variable)!=varmap.end())
	{
		//expmap.insert({variable,varmap[variable]});
		expmap[variable] = varmap[variable];
		cout<<"exported to all childs "<<endl;
	}
	else
	{
		cout<<"var not found"<<endl;
	}
}

void executeShellCommand(string input)
{
	int child = fork();
	char *args[2];
	if(child==0)
	{
		/*for(auto i : varmap)
		{
			cout<<i.first<<" : "<<i.second<<endl;
		}
		
			cout<<"insde child "<<endl;
		for(auto i : varmap)
			{
				cout<<i.first<<" : "<<i.second<<endl;
			}
		//varmap = expmap;
			cout<<endl;*/
		//varmap.clear();
		//varmap = expmap;
		//expmap.clear();
			

		getArgsFromString(input,args);
		//if(fork()==0)
		  execvp(args[0],args);
	}
}






