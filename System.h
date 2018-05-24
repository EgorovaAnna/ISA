#include "Elevator.h"

class System
{
	vector<Elevator> elevators;
	vector<int> counter;
	vector<Task> tasks;
	unsigned int t;
	int height, tnumber;
public:
	System(int quantityEl, int quantityLev);
	void iteration();
	void distribute(int time = 0);
	void newTask(Task nt);
	void newTasks(vector<Task> nt);
	void show();
	int getTime();
	bool allElevatorsStoped();
};
