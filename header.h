#include <string.h>
#include <iostream>
#include <vector>
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

