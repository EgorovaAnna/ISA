all: l2

l2: lift2.o System.o Elevator.o Task.o
	g++ -o l2 lift2.o System.o Elevator.o Task.o
	
lift2.o: lift2.cpp
	g++ -c lift2.cpp
	
System.o: System.cpp
	g++ -c System.cpp
	
Elevator.o: Elevator.cpp
	g++ -c Elevator.cpp
	
Task.o: Task.cpp
	g++ -c Task.cpp
	
clear:
	rm l2 *.o
