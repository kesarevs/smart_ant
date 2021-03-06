all: Smart_Ant

Smart_Ant: STATE.o GENOME.o ANT.o SMART_ANT.o main.o
	g++ STATE.o GENOME.o ANT.o SMART_ANT.o main.o -o Smart_Ant.out

main.o: main.cpp SMART_ANT.h ANT.h GENOME.h STATE.h
	g++ -c main.cpp

SMART_ANT.o: SMART_ANT.cpp SMART_ANT.h ANT.h GENOME.h STATE.h
	g++ -c SMART_ANT.cpp

ANT.o: ANT.cpp ANT.h GENOME.h STATE.h
	g++ -c ANT.cpp

GENOME.o: GENOME.cpp GENOME.h STATE.h
	g++ -c GENOME.cpp

STATE.o: STATE.cpp STATE.h
	g++ -c STATE.cpp

clean:
	rm -rf *.o