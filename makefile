all: l2

l2: lift2.o System.o Elevator.o Task.o
	g++ -o l2 lift2.o System.o Elevator.o Task.o
	
Task.o: Task.cpp Task.h
	g++ -c Task.cpp Task.h
	
Elevator.o: Elevator.cpp Elevator.h
	g++ -c Elevator.cpp Elevator.h Task.h
	
System.o: System.cpp System.h
	g++ -c System.cpp System.h Elevator.h
	
lift2.o: lift2.cpp
	g++ -c lift2.cpp	

clear:
	rm l2 *.o *.gch
