#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h> //for passwd file sturcute
#include <fcntl.h>  

#include <errno.h>


#include <signal.h> 

#define f(i,a,b) for(int i=(int)a;i<=(int)b;i++)


using namespace std;

void printWecomeMessage();

void getArguments(string str,vector<string> &args);

int getArgumentsArray(vector<string> args_vector,char  *args[]);

//isPipeCommands
bool pipecommand(vector<string> & cmd);

void separatePipe(vector<string> source,vector<string> &desti);

void getArgsFromString(string s, char *args[]);



void executePipeCommands(vector<string> cmd);	

//assingment = commmands
bool isAssignmentCommand(string s);

bool executeAssignmentCommand(string s);

string checkForVar(string s);


//inintshell.cpp
void initShell();

void readShellRC();

//export.cpp
bool isExportCommand(string input);

void executeExportCommand(string input);

void executeShellCommand(string input);



//alias
bool isAliasCommand(string s);

void executeAliasCommand(string input);

void printAlias();


string  aliasFilter(string s);

//singnal
