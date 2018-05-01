#include "Task.cpp"

class Elevator
{
	int currentLevel, nextLevel, currentPeople, maxPeople;
	vector<Task> tasks;
public:
	Elevator(int level, int max = 4)
	{
		currentLevel = level;
		nextLevel = level;
		currentPeople = 0;
		maxPeople = max;
	};
	void addTask(Task task, int t = 0)
	{
		int icur, inex, inex2, ipeo, ipeo2;
		if (tasks.empty())
		{
			if (currentLevel != task[0])
				tasks.push_back(Task(currentLevel, task[0], 0, abs(currentLevel - task[0])*10));
			tasks.push_back(Task(task[0], task[1], task[2], abs(currentLevel - task[0])*10 + 20 + abs(task[1] - task[0])*10));
			this -> task(tasks[0][0], tasks[0][2]);
		}
		else
		{
			if (t != 0)
			{
				if (tasks[0][4] >= t)
				{
					icur = currentLevel;
					inex = tasks[0][1];
					if (tasks[0][1] != task[0])
					{
						tasks.erase(tasks.begin());
						tasks.insert(tasks.begin(), Task(currentLevel, task[0], currentPeople, abs(currentLevel - task[0])*10));
						if (abs(task[0] - task[1]) <= abs(task[0] - inex))
						{
							tasks.insert(tasks.begin(), Task(task[0], task[1], currentPeople + task[2]));
							tasks.insert(tasks.begin(), Task(task[1], inex));
						}
						else
						{
							tasks.insert(tasks.begin() + 1, Task(task[0], inex, currentPeople + task[2]));
							tasks.insert(tasks.begin() + 2, Task(inex, task[1], task[2]));
						}
					}
					else
					{
						inex2 = tasks[1][1];
						ipeo2 = tasks[1][2];
						tasks.erase(tasks.begin() + 1);
						if (abs(task[0] - task[1]) <= abs(task[0] - inex2))
						{
							tasks.insert(tasks.begin() + 1, Task(task[0], task[1], ipeo2 + task[2]));
							tasks.insert(tasks.begin() + 2, Task(task[1], inex2, ipeo2));
						}
						else
						{
							tasks.insert(tasks.begin() + 1, Task(task[0], inex2, ipeo2 + task[2]));
							tasks.insert(tasks.begin() + 2, Task(inex, task[1], task[2]));
						}
					}
				}
				else
				{
					for (auto i = tasks.begin() + 1; i < tasks.end(); i++)
					{
						if ((*i)[4] >= t)
						{
							inex = (*i)[1];
							ipeo = (*i)[2];
							if (i == tasks.end() - 1)
							{
								if (abs((*i)[0] - task[1]) >= abs((*i)[0] - inex))
								{
									tasks.erase(i);
									tasks.push_back(Task(currentLevel, task[0], ipeo));
									if (task[1] != inex)
										tasks.push_back(Task(task[0], inex, ipeo + task[2]));
									tasks.push_back(Task(inex, task[1], task[2]));
								}
								else
								{
									tasks.erase(i);
									tasks.push_back(Task(currentLevel, task[0], ipeo));
									tasks.push_back(Task(task[0], task[1], ipeo + task[2]));
									tasks.push_back(Task(task[1], inex, ipeo));
								}
							}
							else
							{
								inex2 = (*(i + 1))[1];
								ipeo2 = (*(i + 1))[2];
								tasks.insert(i, Task((*i)[0], task[0], ipeo));
								i++;
								tasks.erase(i);
								if (abs((*(i - 1))[0] - task[1]) >= abs((*(i - 1))[0] - inex))
								{
									tasks.erase(i);
									tasks.insert(i, Task(task[1], inex2, ipeo2));
									if (inex != task[1])
									{
										tasks.insert(i, Task(inex, task[1], ipeo2 + task[2]));
										tasks.insert(i, Task(task[0], inex, ipeo + task[2]));
									}
									else
									{
										tasks.insert(i, Task(task[0], inex, ipeo + task[2]));
									}
								}
								else
								{
									tasks.insert(i, Task(task[1], inex, ipeo));
									tasks.insert(i, Task(task[0], task[1], ipeo + task[2]));
								}
								break;
							}
						}
					}
				}
			}
			recount();
		}
	};
	vector<Task> getTasks()
	{
		return tasks;
	};
	void task(int next, int people = 0)
	{
		if (currentLevel != next)
			nextLevel = next;
		currentPeople = people;
	};
	void task()
	{
		if (currentLevel == tasks[0][1])
			tasks.erase(tasks.begin());
		if (!tasks.empty())
			task(tasks[0][1], tasks[0][2]);
	};
	void changeLevel()
	{
		if (currentLevel < nextLevel)
			currentLevel++;
		else
			currentLevel--;
		if (!tasks.empty())
			tasks[0][0] = currentLevel;
	};
	void reduce()
	{
		for (auto i = tasks.begin(); i < tasks.end(); i++)
			(*i)[4]--;
	};
	void recount()
	{
		for (auto i = tasks.begin() + 1; i < tasks.end(); i++)
			(*i)[4] = (*(i - 1))[4] + abs((*i)[0] - (*i)[1])*10 + 20;
		//for (auto i = tasks.begin(); i < tasks.end(); i++)
		//	cout << (*i)[0] << " -> " << (*i)[1] << "   " << (*i)[4] << '\n';
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
	void exit(int ep = 0)
	{
		if (ep = 0)
		{
			if (!tasks.empty())
				currentPeople = tasks[0][2];
			else
				currentPeople = 0;
		}
		else
			currentPeople = currentPeople - ep;
	};
	int max()
	{
		return maxPeople;
	};
};
