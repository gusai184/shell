#include "header.h"
int p[2];
extern vector<int> vectalarm;
extern vector<pair<time_t,string>> allalarm;

void checkMissedAlarms()
{

	//cout<<"Reading missed alarms "<<endl;
	ifstream infile("alarm.txt");
	
	for(string line;getline( infile, line);)
	{
		//	cout<<line<<endl;
		time_t timestamp = stoll(line.substr(0,line.find(":")));
		string msg = line.substr(line.find(":")+1);
	//	cout<<timestamp<<"  =  "<<msg<<endl;
		if(time((time_t *)0)>timestamp)
		{
			cout<<"Missed Alarm "<<timestamp <<" : "<<msg<<endl;
			continue;
		}
		else
		{
			//cout<<"Set Alarm "<<timestamp<<" : "<<msg;
			checkAlarm(timestamp,msg);
		}
	}
	infile.close();

}

void checkAlarm(time_t alarmtime,string msg)
{
	
	int child=fork();
	if(child==0)
	{
		while(time((time_t *)0)!=alarmtime){
		}
		cout<<"Alarm : "<<msg<<" " << time((time_t *)0)<<"\n";
		exit(1);
	}
	else
	{
		vectalarm.push_back(child);
	}

}
	
void alarmHandler(int x,string msg)
{
	time_t curtime = time((time_t*)0);
	time_t alarmtime	 = curtime + x;
	cout<<"Alarm set : "<<curtime<<":"<<alarmtime<<" : "<<msg<<endl<<endl;
	allalarm.push_back(make_pair(alarmtime,msg));
	checkAlarm(alarmtime,msg);
	return;
}


void alarmExit()
{

	for(int i=0;i<vectalarm.size();i++)
	{
		kill(vectalarm[i],SIGKILL);
	}
	
	int fd = open("alarm.txt",O_WRONLY | O_TRUNC | O_CREAT,0644);
	
	if(fd==-1)	
	{
		cout<<"Not able to open alarm file";
		return;
	}
	cout<<"alarm Exit"<<endl;
	for(auto alm : allalarm)
	{
		if(alm.first > time((time_t *)0))
		{
			string alarm_record = to_string(alm.first)+":"+alm.second+"\n";
			cout<<alarm_record<<endl;
			write(fd,alarm_record.c_str(),alarm_record.size());
		}
	}
	close(fd);
}