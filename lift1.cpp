#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

class Task
{
	int from, to, people, elevator;
public:
	Task(int a, int b, int c = 1)
	{
		from = a; to = b; people = c; elevator = -1;
	};
	int & operator[](int a)
	{
		if (a == 0)
			return from;
		if (a == 1)
			return to;
		if (a == 2)
			return people;
		return elevator;
	};
	void appoint(int el)
	{
		elevator = el;
	};
};
class Elevator
{
	int currentLevel, nextLevel, currentPeople, maxPeople;
public:
	Elevator(int level, int max = 4)
	{
		currentLevel = level;
		nextLevel = level;
		currentPeople = 0;
		maxPeople = max;
	};
	void task(int next, int people = 0)
	{
		if (currentLevel != next)
			nextLevel = next;
		currentPeople = people;
	};
	void changeLevel()
	{
		if (currentLevel < nextLevel)
			currentLevel++;
		else
			currentLevel--;
	};
	int getLevel()
	{
		return currentLevel;
	};
	int getNext()
	{
		return nextLevel;
	};
	int getPeople()
	{
		return currentPeople;
	};
	void exit()
	{
		currentPeople = 0;
	};
	int max()
	{
		return maxPeople;
	};
};
class System
{
	vector<Elevator> elevators;
	vector<int> counter;
	vector<Task> tasks;
	unsigned int t;
	int height;
public:
	System(int quantityEl, int quantityLev)
	{
		height = quantityLev;
		for(int i = 0; i < quantityEl; i++)
		{
			elevators.push_back(Elevator(rand()%height));
			counter.push_back(0);
		}
		t = 0;
	};
	void iteration()
	{
		t++;
		for (int i = 0; i < elevators.size(); i++)
		{
			if (elevators[i].getLevel() != elevators[i].getNext())
			{
				if (counter[i] == 10)
				{
					elevators[i].changeLevel();
					counter[i] = 1;
				}
				else
					counter[i]++;
			}
			else
			{
				if (elevators[i].getPeople() != 0)
				{
					if (counter[i] == 20)
					{
						elevators[i].exit();
						counter[i] = 0;
					}
					else
						counter[i]++;
				}
				else
				{
					for (auto j = tasks.begin(); j < tasks.end(); j++)
					{
						if ((*j)[3] == i)
						{
							if ((*j)[0] != -1)
							{
								elevators[i].task((*j)[0]);
								(*j)[0] = -1;
							}
							else
							{
								elevators[i].task((*j)[1], (*j)[2]);
								tasks.erase(j);
							}
						}
					}
				}
			}
		}
	};
	void distribute()
	{
		int el = height*30, k, eln;
		for (int i = 0; i < elevators.size(); i++)
		{
			t++;
			if ((k = abs(elevators[i].getLevel() - tasks.back()[0])*10) < el)
			{
				eln = i;
				el = k;
				if (k == 0)
					break;
			}
		}
		tasks.back().appoint(eln);
	};
	void newTask(Task nt)
	{
		tasks.push_back(nt);
		cout << "new task added: from " << nt[0] << " level to " << nt[1] << " level" << '\n';
		distribute();
	};
	void show()
	{
		for (int i = 0; i < elevators.size(); i++)
			cout << elevators[i].getLevel() << (elevators[i].getLevel() < 10 ? " " : "") << "   |   ";
		cout << '\n';
	};
	int getTime()
	{
		return t; 
	};
	bool allElevatorsStoped()
	{
		for (int i = 0; i < elevators.size(); i++)
			if (tasks.size() != 0 || elevators[i].getLevel() != elevators[i].getNext() || counter[i] != 0)
				return false;
		return true;
	};
};

int main()
{
	int i, elevators = 7, levels = 50;
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
		if (i%10 == 0)
			sys.show();
	}
	cout << "All movement and calculation took " << sys.getTime() << '\n';
}
