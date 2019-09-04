#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_map>

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h> //for passwd file sturcute
#include <fcntl.h>  

#define f(i,a,b) for(int i=(int)a;i<=(int)b;i++)


using namespace std;

void printWecomeMessage();

void printPrompt();

void getArguments(string str,vector<string> &args);

int getArgumentsArray(vector<string> args_vector,char  *args[]);

//pipecommands
bool pipecommand(vector<string> & cmd);

void separatePipe(vector<string> source,vector<string> &desti);

void getArgsFromString(string s, char *args[]);

void executePipeCommands(vector<string> cmd);	