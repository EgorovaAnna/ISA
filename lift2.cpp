#include "System.cpp"

int main()
{
	int i, count = 70, elevators = 7, levels = 50, p = 7, pn, cnt;
	srand (time(NULL));
	vector<Task> nt;
	System sys(elevators, levels);
	cout << '\n' << "Positions of elevators in the beginning:" << '\n';
	for (i = 1; i < elevators + 1; i++)
		cout << i << "        ";
	cout << '\n';
	sys.show();
	sys.newTask(Task(rand()%50, rand()%50));
	sys.iteration();
	while (!sys.allElevatorsStoped())
	{
		sys.iteration();
		pn = rand()%350;
		if (pn <= p && count >= 0)
		{
			sys.newTask(Task(rand()%50, rand()%50));
			count--;
		}
		if (pn <= 2 && count > 0)
		{
			cnt = 5 + rand()%20;
			for (i = 0; i < cnt; i++)
				nt.push_back(Task(rand()%50, rand()%25));
			sys.newTasks(nt);
			nt.clear();
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
