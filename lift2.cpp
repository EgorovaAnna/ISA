#include "System.h"

int main()
{
	int i, count = 100, elevators = 7, levels = 50, p = 25, pn, pThrow_in = 1, countThrow_in;
	srand (time(NULL));
	vector<Task> nt;
	System sys(elevators, levels);
	cout << '\n' << "Positions of elevators in the beginning:" << '\n';
	for (i = 1; i < elevators + 1; i++)
		cout << i << "        ";
	cout << '\n' << '\n';
	sys.show();
	sys.newTask(Task(rand()%50, rand()%50));
	sys.iteration();
	while (!sys.allElevatorsStoped())
	{
		sys.iteration();
		pn = rand()%1000;
		if (pn <= p && count >= 0)
		{
			sys.newTask(Task(rand()%50, rand()%50));
			count--;
		}
		if (pn >= 1000 - pThrow_in && count > 0)
		{
			countThrow_in = 5 + rand()%20;
			for (i = 0; i < countThrow_in; i++)
				nt.push_back(Task(10 + rand()%40, rand()%25));
			sys.newTasks(nt);
			nt.clear();
			count -= countThrow_in;
		}
	}
	cout << '\n' << "Positions of elevators at the end:" << '\n';
	for (i = 0; i < elevators; i++)
		cout << i + 1 << "        ";
	cout << '\n';
	sys.show();
	cout << '\n' << '\n' << '\n';
	cout << "All movement and calculation took " << sys.getTime() << '\n';
}
