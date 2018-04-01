#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
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
	int currentLevel;
	int nextLevel;
	int currentPeople;
public:
	Elevator(int level, int max = 10)
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
						if ((*j)[4] == i)
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
	};
	void distribute()
	{
		int el = height*30, eln;
		for (auto j = tasks.begin(); j < tasks.end(); j++)
		{
			if ((*j)[4] == -1)
			{
				for (int i = 0; i < elevators.size(); i++)
				{
					if (elevators[i].getLevel() == elevators[i].getNext() && (k = abs(elevators[i].getLevel() - tasks.back()[0])*10) < el)
					{
						eln = i;
						el = k;
						if (k == 0)
							break;
					}
					if (elevators[i].getLevel() != elevators[i].getNext())
					{
						if ((elevators[i].getLevel() - elevators[i].getNext())*(elevators[i].getLevel() - (*j)[0]) > 0 && elevators[i].getPeople() + (*j)[3] <= elevators[i].max())
							if ((elevators[i].getLevel() - elevators[i].getNext())*((*j)[0] - (*j)[1]) > 0 && (elevators[i].getLevel() - (*j)[0])*10 < el)
								eln = i;
					}
				}
				(*j)[4] = eln;
			}
		}
	};
	void newTask(Task nt)
	{
		tasks.push_back(nt);
		distribute();
	};
	void show()
	{
		for (int i = 0; i < elevators.size(); i++)
			cout << elevators[i].getLevel() << "     ";
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
	int i;
	srand (time(NULL));
	System sys(7, 50);
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
	cout << sys.getTime() << '\n';
}
