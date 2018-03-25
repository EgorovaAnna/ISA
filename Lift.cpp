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
	Elevator(int level)
	{
		currentLevel = level;
		nextLevel = level;
		currentPeople = 0;
	};
	void task(int next)
	{
		if (currentLevel != next)
			nextLevel = next;
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
					counter[i] = 0;
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
						if (*j[4] == i)
							elevators[i].task(*j[1]);
					}
				}
		}
	};
};
