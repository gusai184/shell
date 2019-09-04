all:shell


shell: mainfile1.o functions.o
	g++ mainfile1.o functions.o  -o shell

mainfile1.o: mainfile1.cpp 
	g++ -c mainfile1.cpp 

functions.o: functions.cpp
	g++ -c functions.cpp

