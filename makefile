all:shell


shell: main.o functions.o pipecmd.o
	g++ main.o functions.o pipecmd.o -o shell

main.o: main.cpp 
	g++ -c main.cpp 

functions.o: functions.cpp
	g++ -c functions.cpp

pipecmd.o: pipecmd.cpp
	g++ -c pipecmd.cpp

rm:
	rm  main.o functions.o pipecmd.o 
