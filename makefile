all:shell


shell: mainfile.o functions.o
	g++ mainfile.o functions.o  -o shell

mainfile.o: mainfile.cpp 
	g++ -c mainfile.cpp 

functions.o: functions.cpp
	g++ -c functions.cpp

