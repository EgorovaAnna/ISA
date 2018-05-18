#include "Task.cpp"

class Elevator
{
	int currentLevel, nextLevel, currentPeople, maxPeople, counter;
	vector<Task> tasks;
public:
	Elevator(int level, int max = 4)
	{
		currentLevel = level;
		nextLevel = level;
		currentPeople = 0;
		maxPeople = max;
		counter = 0;
	};
	void addTask(Task task, int t = 0)
	{
		int icur, inex, inex2, ipeo, ipeo2, buf = 1, flag = 0, er = 0, time = 0;
		vector<Task> nt;
		auto place = tasks.begin();
		if (currentLevel == task[0] && task[0] < 20)
		{
			counter = 20;
			if (!tasks.empty())
				tasks[0][4] = 20;
		}
		if (!tasks.empty() && currentLevel == task[0] && t <= 20)
		{
			if (tasks[0][1] == task[0])
			{
				buf = tasks[0][4];
				tasks[0][4] = 20;
				recount();
				t = 21;
			}
			else
			{
				if (abs(tasks[0][0] - tasks[0][1]) >= abs(tasks[0][0] - task[1]))
				{
					inex = tasks[0][1];
					tasks.erase(tasks.begin());
					tasks.insert(tasks.begin(), Task(currentLevel, currentLevel, currentPeople, 20));
					tasks.insert(tasks.begin() + 1, Task(currentLevel, task[1], currentPeople + task[2], abs(currentLevel - task[1])*10 + 40));
					if (task[1] != inex)
						tasks.insert(tasks.begin() + 2, Task(task[1], inex, currentPeople));
					t = 0;
				}
				else
				{
					inex = tasks[0][1];
					tasks[0][2] += task[2];
					tasks.insert(tasks.begin(), Task(currentLevel, currentLevel, currentPeople, 20));
					recount();
					task[0] = inex;
					t = tasks[1][4]; 
				}
				this -> task();
			}
			buf = 0;
		}
		if (buf == 1 && (tasks.empty() || tasks.back()[4] < t))
		{
			if (tasks.empty())
			{
				tasks.push_back(Task(currentLevel, task[0], 0, abs(currentLevel - task[0])*10 + 20));
				tasks.push_back(Task(task[0], task[1], task[2], tasks[0][4] + abs(task[0] - task[1])*10 + 20));
				this -> task();
			}
			else
			{
				if (tasks.size() == 1 && tasks.back()[0] == task[0])
				{
					counter = 20;
					inex = tasks[0][1];
					ipeo = tasks[0][2];
					tasks.clear();
					tasks.push_back(Task(currentLevel, currentLevel, ipeo, 20));
					if (currentLevel != inex && abs(currentLevel - task[1]) >= abs(currentLevel - inex))
					{
						tasks.push_back(Task(currentLevel, inex, ipeo + task[2], 20 + abs(currentLevel - inex)*10));
						if (inex != task[1])
							tasks.push_back(Task(inex, task[1], task[2]));
					}
					if (abs(currentLevel - task[1]) < abs(currentLevel - inex))
					{
						tasks.push_back(Task(currentLevel, task[1], ipeo + task[2], 20 + abs(currentLevel - task[1])*10));
						tasks.push_back(Task(task[1], inex, ipeo));
					}
					this -> task();
				}
				else
				{
					time = max(tasks.back()[4], 0);
					if (tasks.back()[1] != task[0])
						tasks.push_back(Task(tasks.back()[1], task[0], 0, time + abs(tasks.back()[1] - task[0])*10 + 20));
					tasks.push_back(Task(task[0], task[1], task[2], time + abs(task[0] - task[1])*10 + 20));
				}
			}
		}
		else
		{
			if (t != 0)
			{
				for (auto i = tasks.begin(); i < tasks.end(); i++)
				{
					if ((*i)[4] >= t && (task[0] >= min((*i)[0], (*i)[1]) && task[0] <= max((*i)[0], (*i)[1])))
					{
						if (i != tasks.begin())
							time = (*(i - 1))[4];
						else
							time = (*i)[4]%10;
						if (time < 0 || task[0] == tasks[0][0])
							time = 0;
						place = i;
						inex = (*i)[1];
						inex2 = (*i)[0];
						ipeo = (*i)[2];
						if (i == tasks.end() - 1)
						{
							if (abs((*i)[0] - task[1]) >= abs((*i)[0] - inex))
							{
								er++;
								if (inex2 != task[0] || i == tasks.begin())
									nt.push_back(Task(inex2, task[0], ipeo, time + abs(inex2 - task[0])*10 + 20));
								nt.push_back(Task(task[0], inex, ipeo + task[2]));
								if (task[1] != inex)
									nt.push_back(Task(inex, task[1], task[2]));
							}
							else
							{
								er++;
								nt.push_back(Task(inex2, task[0], ipeo, time + abs(inex2 - task[0])*10 + 20));
								nt.push_back(Task(task[0], task[1], ipeo + task[2]));
								nt.push_back(Task(task[1], inex, ipeo));
							}
						}
						else
						{
							inex2 = (*(i + 1))[1];
							ipeo2 = (*(i + 1))[2];
							buf = (*i)[0];
							er++;
							if (buf != task[0] || i == tasks.begin())
								nt.push_back(Task(buf, task[0], ipeo, time + abs(buf - task[0])*10 + 20));
							if (abs(task[0] - task[1]) >= abs(task[0] - inex))
							{
								buf = task[0];
								if (inex != task[0])
									nt.push_back(Task(buf, inex, ipeo + task[2]));
								i++;
								while (abs(task[0] - (*i)[1]) < abs(task[0] - task[1]) && i < tasks.end())
								{
									buf = inex;
									er++;
									inex = (*i)[1];
									ipeo = (*i)[2];
									nt.push_back(Task(buf, inex, ipeo + task[2]));
									i++;
								}
								if (inex != task[1])
								{
									nt.push_back(Task(inex, task[1], task[2] + ((i < tasks.end() - 1) ? 0 : (*(i + 1))[2])));
									if (i < tasks.end())
									{
										er++;
										inex = (*i)[1];
										ipeo = (*i)[2];
										nt.push_back(Task(task[1], inex, ipeo));
									}
								}
							}
							else
							{
								nt.push_back(Task(task[0], task[1], ipeo + task[2]));
								nt.push_back(Task(task[1], inex, ipeo));
							}
						}
						break;
					}
				}
				tasks.erase(place, place + er);
				tasks.insert(place, nt.begin(), nt.end());
				for (auto i = tasks.begin(); i < tasks.end(); i++)
				{
					if (i > tasks.begin() && (*i)[0] != (*(i - 1))[1])
					{
						tasks.insert(i, Task((*(i - 1))[1], (*i)[1], (*i)[2]));
						tasks.erase(i + 1);
					}
				}
			}
		}
		for (auto i = tasks.begin(); i < tasks.end(); i++)
			if (i > tasks.begin() && (*i)[0] != (*(i - 1))[1])
			{
				tasks.insert(i, Task((*(i - 1))[1], (*i)[1], (*i)[2]));
				tasks.erase(i + 1);
			}
		recount();
		if (nextLevel != tasks[0][1])
			this -> task(tasks[0][1], tasks[0][2]);
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
	void task(bool stop = false)
	{
		if (tasks[0][4] <= 0 || stop)
			tasks.erase(tasks.begin());
		if (!tasks.empty())
		{
			if (tasks[0][1] == currentLevel)
				counter = 20;
			task(tasks[0][1], tasks[0][2]);
		}
	};
	void changeLevel()
	{
		if (currentLevel < nextLevel)
			currentLevel++;
		else
			currentLevel--;
		if (currentLevel == nextLevel)
			counter = 20;
		if (!tasks.empty())
		{
			tasks[0][0] = currentLevel;
			tasks[0][4] = abs(currentLevel - nextLevel)*10 + 21;
		}
	};
	int reduce()
	{
		if (!tasks.empty())
		{
			if (tasks[0][1] != nextLevel)
				task();
			else
				if (currentLevel == nextLevel)
				{
					counter--;
					if (counter < 0)
					{
						task(true);
						recount();
						counter = 0;
						return -1;
					}
					if (counter == 19)
						return -1;
				}
			for (auto i = tasks.begin(); i < tasks.end(); i++)
			{
				(*i)[4]--;
				if ((*i)[4] < 20 && (*i)[0] != (*i)[1])
					recount();
				if ((*i)[4] < 0)
					task(true);
			}
		}
		return 0;
	};
	void recount()
	{
		int buf = 0;
		tasks[0][0] = currentLevel;
		if (tasks[0][0] != tasks[0][1])
		{
			counter = 0;
			if (tasks[0][4]%10 != 0)
				buf = tasks[0][4]%10 - 10;
			if (tasks[0][4] < abs(tasks[0][0] - tasks[0][1])*10)
				tasks[0][4] = abs(tasks[0][0] - tasks[0][1])*10 + 20 + buf;
		}
		else
			if (tasks[0][4] > 20)
				tasks[0][4] = 19;
		for (auto i = tasks.begin() + 1; i < tasks.end(); i++)
		{
			if ((*i)[0] == (*i)[1])
				tasks.erase(i);
			(*i)[4] = (*(i - 1))[4] + abs((*i)[0] - (*i)[1])*10 + 20;
			if ((*i)[0] != (*(i - 1))[1])
			{
				cout << "WTF?! " <<  (*(i - 1))[1] << "---" << (*(i))[0] << '\n';
				tasks.erase(i);
				recount();
			}
		}
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
	int getCounter()
	{
		return counter;
	};
	void exit(int ep = 0)
	{
		counter = 1;
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
	int getMax()
	{
		return maxPeople;
	};
};
