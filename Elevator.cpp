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
		int icur, inex, inex2, ipeo, ipeo2, buf, flag = 0;
		vector<Task> nt;
		auto place = tasks.begin();
		if (tasks.empty() || tasks.back()[4] < t)
		{
			if (tasks.empty())
			{
				tasks.push_back(Task(currentLevel, task[0], 0, abs(currentLevel - task[0])*10 + 20));
				tasks.push_back(Task(task[0], task[1], task[2], tasks[0][4] + abs(task[0] - task[1])*10 + 20));
				this -> task();
			}
			else
			{
				tasks.push_back(Task(tasks.back()[1], task[0], 0));
				tasks.push_back(Task(task[0], task[1], task[2]));
			}
		}
		else
		{
			if (t != 0)
			{
				cout << "t = " << t << "; " << task[0] << "---" << task[1] << '\n';
				if (tasks[0][4] >= t)
				{
					icur = currentLevel;
					inex = tasks[0][1];
					if (tasks[0][1] != task[0])
					{
						cout << "erase : " <<  tasks[0][0] << " --- " << tasks[0][1] << '\n';
						buf = tasks[0][4];
						tasks.erase(tasks.begin());
						//tasks.insert(tasks.begin(), Task(currentLevel, task[0], currentPeople, abs(currentLevel - task[0])*10 - buf%10 + 20));
						//cout << "insert new : " <<  tasks[0][0] << " --- " << tasks[0][1] << "   t = " << tasks[0][4] << '\n';
						nt.push_back(Task(currentLevel, task[0], currentPeople, abs(currentLevel - task[0])*10 - buf%10 + 20));
						if (abs(task[0] - task[1]) <= abs(task[0] - inex))
						{
							//tasks.insert(tasks.begin() + 1, Task(task[0], task[1], currentPeople + task[2]));
							//cout << "insert new : " <<  tasks[1][0] << " --- " << tasks[1][1] << '\n';
							nt.push_back(Task(task[0], task[1], currentPeople + task[2]));
							if (task[1] != inex)
							{
								//tasks.insert(tasks.begin() + 2, Task(task[1], inex, currentPeople));
								//cout << "insert new : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
								nt.push_back(Task(task[1], inex, currentPeople));
							}
						}
						else
						{
							place++;
							//tasks.insert(tasks.begin() + 1, Task(task[0], inex, currentPeople + task[2]));
							//cout << "insert new : " <<  tasks[1][0] << " --- " << tasks[1][1] << '\n';
							nt.push_back(Task(task[0], inex, currentPeople + task[2]));
							if (tasks.size() > 2)
							{
								inex2 = tasks[2][1];
								ipeo2 = tasks[2][2];
								if (abs(inex - task[1]) >= abs(inex - inex2))
								{
									tasks[2][2] += task[2];
									if (tasks.size() > 3)
									{
										inex = tasks[3][1];
										ipeo = tasks[3][2];
										cout << "erase : " <<  tasks[3][0] << " --- " << tasks[3][1] << '\n';
										tasks.erase(tasks.begin() + 3);
										cout << "erase : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
										tasks.erase(tasks.begin() + 2);
										nt.push_back(tasks[2]);
										nt.push_back(Task(inex2, task[1], ipeo + task[2]));
										nt.push_back(Task(task[1], inex, ipeo));
										//tasks.insert(tasks.begin() + 3, Task(inex2, task[1], ipeo + task[2]));
										//cout << "insert new : " <<  tasks[3][0] << " --- " << tasks[3][1] << '\n';
										//tasks.insert(tasks.begin() + 4, Task(task[1], inex, ipeo));
										//cout << "insert new : " <<  tasks[4][0] << " --- " << tasks[4][1] << '\n';
									}
									else
									{
										//tasks.push_back(Task(inex2, task[1], task[2]));
										//cout << "insert new : " <<  tasks[3][0] << " --- " << tasks[3][1] << '\n';
										cout << "erase : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
										tasks.erase(tasks.begin() + 2);
										nt.push_back(tasks[2]);
										nt.push_back(Task(inex2, task[1], task[2]));
									}
								}
								else
								{
									cout << "erase : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
									tasks.erase(tasks.begin() + 2);
									//tasks.insert(tasks.begin() + 2, Task(inex, task[1], task[2] + ipeo2));
									//cout << "insert new : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
									//tasks.insert(tasks.begin() + 3, Task(task[1], inex2, ipeo2));
									//cout << "insert new : " <<  tasks[3][0] << " --- " << tasks[3][1] << '\n';
									nt.push_back(Task(inex, task[1], task[2] + ipeo2));
									nt.push_back(Task(task[1], inex2, ipeo2));
								}
							}
							else
							{
								//tasks.push_back(Task(inex, task[1], task[2]));
								//cout << "insert new : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
								nt.push_back(Task(inex, task[1], task[2]));
							}
						}
					}
					else
					{
						if (tasks.size() > 1)
						{
							place++;
							inex2 = tasks[1][1];
							ipeo2 = tasks[1][2];
							cout << "erase : " <<  tasks[1][0] << " --- " << tasks[1][1] << '\n';
							tasks.erase(tasks.begin() + 1);
							if (abs(task[0] - task[1]) <= abs(task[0] - inex2))
							{
								//tasks.insert(tasks.begin() + 1, Task(task[0], task[1], ipeo2 + task[2]));
								//cout << "insert new : " <<  tasks[1][0] << " --- " << tasks[1][1] << '\n';
								nt.push_back(Task(task[0], task[1], ipeo2 + task[2]));
								if (task[1] != inex2)
								{
									//tasks.insert(tasks.begin() + 2, Task(task[1], inex2, ipeo2));
									//cout << "insert new : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
									nt.push_back(Task(task[1], inex2, ipeo2));
								}
							}
							else
							{
								if (tasks.size() > 2)
								{
									inex = tasks[2][1];
									ipeo = tasks[2][2];
									cout << "erase : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
									tasks.erase(tasks.begin() + 2);
									//tasks.insert(tasks.begin() + 1, Task(task[0], inex2, ipeo2 + task[2]));
									//cout << "insert new : " <<  tasks[1][0] << " --- " << tasks[1][1] << '\n';
									//tasks.insert(tasks.begin() + 2, Task(inex2, task[1], task[2] + ipeo));
									//cout << "insert new : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
									//tasks.insert(tasks.begin() + 3, Task(task[1], inex, ipeo));
									//cout << "insert new : " <<  tasks[3][0] << " --- " << tasks[3][1] << '\n';
									nt.push_back(Task(task[0], inex2, ipeo2 + task[2]));
									nt.push_back(Task(inex2, task[1], task[2] + ipeo));
									nt.push_back(Task(task[1], inex, ipeo));
								}
								else
								{
									//tasks.insert(tasks.begin() + 1, Task(task[0], inex2, ipeo2 + task[2]));
									//cout << "insert new : " <<  tasks[1][0] << " --- " << tasks[1][1] << '\n';
									//tasks.insert(tasks.begin() + 2, Task(inex2, task[1], task[2]));
									//cout << "insert new : " <<  tasks[2][0] << " --- " << tasks[2][1] << '\n';
									nt.push_back(Task(task[0], inex2, ipeo2 + task[2]));
									nt.push_back(Task(inex2, task[1], task[2]));
								}
							}
						}
						else
						{
							place++;
							//tasks.push_back(Task(tasks[0][1], task[1], task[2]));
							//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
							nt.push_back(Task(tasks[0][1], task[1], task[2]));
						}
					}
				}
				else
				{
					for (auto i = tasks.begin() + 1; i < tasks.end(); i++)
					{
						//cout << "t12 = " <<  (*i)[4] << "; " << (*i)[0] << "---" << (*i)[1] << '\n';
						//cout << (*i)[0] << " --- " << (*i)[1] << '\n';
						if ((*i)[4] >= t || (task[0] >= min((*i)[0], (*i)[1]) && task[0] <= max((*i)[0], (*i)[1])))
						{
							place = i;
							inex = (*i)[1];
							inex2 = (*i)[0];
							ipeo = (*i)[2];
							if (i == tasks.end() - 1)
							{
								if (abs((*i)[0] - task[1]) >= abs((*i)[0] - inex))
								{
									cout << "erase last: " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									tasks.erase(i);
									if (inex2 != task[0])
									{
										//tasks.push_back(Task(inex2, task[0], ipeo));
										//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
										nt.push_back(Task(inex2, task[0], ipeo));
									}
									//tasks.push_back(Task(task[0], inex, ipeo + task[2]));
									//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
									nt.push_back(Task(task[0], inex, ipeo + task[2]));
									if (task[1] != inex)
									{
										//tasks.push_back(Task(inex, task[1], task[2]));
										//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
										nt.push_back(Task(inex, task[1], task[2]));
									}
									//else
									//	tasks.push_back(Task(task[0], inex, ipeo + task[2]));
								}
								else
								{
									cout << "erase last: " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									tasks.erase(i);
									//tasks.push_back(Task(inex2, task[0], ipeo));
									//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
									//tasks.push_back(Task(task[0], task[1], ipeo + task[2]));
									//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
									nt.push_back(Task(inex2, task[0], ipeo));
									nt.push_back(Task(task[0], task[1], ipeo + task[2]));
									if (task[1] != inex)
									{
										//tasks.push_back(Task(task[1], inex, ipeo));
										//cout << "pushback new : " <<  tasks.back()[0] << " --- " << tasks.back()[1] << '\n';
										nt.push_back(Task(task[1], inex, ipeo));
									}
								}
							}
							else
							{
								inex2 = (*(i + 1))[1];
								ipeo2 = (*(i + 1))[2];
								buf = (*i)[0];
								cout << "erase : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
								tasks.erase(i);
								//tasks.insert(i, Task(buf, task[0], ipeo));
								//cout << "insert new : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
								nt.push_back(Task(buf, task[0], ipeo));
								i++;
								//if (abs((*(i - 1))[0] - task[1]) >= abs((*(i - 1))[0] - inex))
								if (abs(task[0] - task[1]) >= abs(task[0] - inex))
								{
									cout << "erase : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									tasks.erase(i);
									//tasks.insert(i, Task(task[1], inex2, ipeo2));
									//cout << "insert new : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									/*if (inex != task[1])
									{
										tasks.insert(i, Task(inex, task[1], ipeo2 + task[2]));
										cout << "insert new : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									}
									if (inex != task[0])
									{
										tasks.insert(i, Task(task[0], inex, ipeo + task[2]));
										cout << "insert new : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									}*/
									if (inex != task[0])
										nt.push_back(Task(task[0], inex, ipeo + task[2]));
									if (inex != task[1])
										nt.push_back(Task(inex, task[1], ipeo2 + task[2]));
									nt.push_back(Task(task[1], inex2, ipeo2));
								}
								else
								{
									//tasks.insert(i, Task(task[1], inex, ipeo));
									//cout << "insert new : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									//tasks.insert(i, Task(task[0], task[1], ipeo + task[2]));
									//cout << "insert new : " <<  (*i)[0] << " --- " << (*i)[1] << '\n';
									nt.push_back(Task(task[0], task[1], ipeo + task[2]));
									nt.push_back(Task(task[1], inex, ipeo));
								}
							}
							break;
						}
					}
				}
			}
			tasks.insert(place, nt.begin(), nt.end());
			for (auto i = nt.begin(); i < nt.end(); i++)
				cout << (*i)[0] << "_" << (*i)[1] << "; ";
			cout << '\n';
		}
		if (tasks.size() > 1)
			recount();
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
		if (tasks[0][4] <= 0)
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
		{
			tasks[0][0] = currentLevel;
			tasks[0][4] = abs(currentLevel - nextLevel)*10 + 20;
		}
	};
	void reduce()
	{
		if (!tasks.empty())
			for (auto i = tasks.begin(); i < tasks.end(); i++)
			{
				(*i)[4]--;
				if ((*i)[4] < 0)
				{
					if ((*i)[0] != (*i)[1] || i != tasks.begin())
						cout << "??? " << (*i)[0] << "  --- " << (*i)[1] << '\n';
					if (currentLevel == nextLevel)
						task();
					//tasks[0][4] = abs(currentLevel - nextLevel)*10 + 20;
					if (tasks.size() > 1)
						recount();
				}
			}
	};
	void recount()
	{
		//cout << "(" << tasks[0][0] << " -> " << tasks[0][1] << ") = "<<  tasks[0][4] << "     ";
		if (tasks[0][0] != tasks[0][1])
			tasks[0][4] = tasks[0][4]%10 + abs(tasks[0][0] - tasks[0][1])*10 + 20;
		cout << "(" << tasks[0][0] << " -> " << tasks[0][1] << ") = "<<  tasks[0][4] << "     ";
		for (auto i = tasks.begin() + 1; i < tasks.end(); i++)
		{
			(*i)[4] = (*(i - 1))[4] + abs((*i)[0] - (*i)[1])*10 + 20;
			cout << "(" << (*i)[0] << " -> " << (*i)[1] << ") = "<<  (*i)[4] << "     ";
			if ((*i)[0] != (*(i - 1))[1])
			{
				cout << "WTF?!  " << (*i)[0] << "   " << (*(i - 1))[1] << '\n';
				tasks.erase(i);
				recount();
			}
		}
		cout << '\n';
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
			//if (tasks[0][2])
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
