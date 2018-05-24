#include "Task.h"

class Elevator
{
	int currentLevel, nextLevel, currentPeople, maxPeople, counter;
	vector<Task> tasks;
public:
	Elevator(int level, int max = 4);
	void addTask(Task task, int t = 0);
	vector<Task> getTasks();
	void task(int next, int people = 0);
	void task(bool stop = false);
	void changeLevel();
	int reduce();
	void recount();
	int getLevel();
	int getNext();
	int getMax();
	int getPeople();
	int getCounter();
	void exit(int ep = 0);
};
