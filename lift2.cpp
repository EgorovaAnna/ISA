#include "System.cpp"

int main()
{
	int i, count = 70, elevators = 7, levels = 50, p = 7, pn;
	srand (time(NULL));
	System sys(elevators, levels);
	cout << '\n' << "Positions of elevators in the beginning:" << '\n';
	for (i = 0; i < elevators; i++)
		cout << i << "        ";
	cout << '\n';
	i = 0;
	sys.show();
	sys.newTask(Task(rand()%50, rand()%50));
	sys.iteration();
	while (!sys.allElevatorsStoped())
	{
		sys.iteration();
		i++;
		pn = rand()%350;
		if (pn <= p && count >= 0)
		{
			sys.newTask(Task(rand()%50, rand()%50));
			count--;
		}
			
	}
	cout << '\n' << "Positions of elevators at the end:" << '\n';
	for (i = 0; i < elevators; i++)
		cout << i << "        ";
	cout << '\n';
	sys.show();
	cout << '\n' << '\n' << '\n';
	cout << "All movement and calculation took " << sys.getTime() << '\n';
}
