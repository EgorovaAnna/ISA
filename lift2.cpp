#include "System.cpp"

int main()
{
	int i, count = 3, elevators = 7, levels = 50;
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
	while (!sys.allElevatorsStoped() && i < 1000)
	{
		sys.iteration();
		i++;
		//if (i%10 == 0)
			//sys.show();
		if (i%48 == 0 && count >= 0)
		{
			sys.newTask(Task(rand()%50, rand()%50));
			count--;
		}
			
	}
	cout << "All movement and calculation took " << sys.getTime() << '\n';
}
