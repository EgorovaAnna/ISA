#include "Elevator.cpp"

class System
{
	vector<Elevator> elevators;
	vector<int> counter;
	vector<Task> tasks;
	unsigned int t;
	int height, tnumber;
public:
	System(int quantityEl, int quantityLev)
	{
		height = quantityLev;
		tnumber = 0;
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
		vector<Task> itasks;
		//cout << t << " it " << '\n';
		for (int i = 0; i < elevators.size(); i++)
		{
			itasks = elevators[i].getTasks();
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
					if (!itasks.empty())
						elevators[i].task();
					/*inext = -1; iinext = -1;
					if (!itasks.empty())
					{
						for (int j = itasks[0]; j < itasks.size(); j++)
						{
							if ((*j)[0] == -1)
								if (abs(itasks[inext][1] - elevators[i].getLevel()) > abs(itasks[j][1] - elevators[i].getLevel()))
									inext = j;
							else
								if (abs(itasks[iinext][0] - elevators[i].getLevel()) > abs(itasks[j][0] - elevators[i].getLevel()))
									iinext = j;
						}
						if (inext == -1)
						{
							elevators[i].task(tasks[iinext][0]);
							tasks[iinext][0] = -1;
						}
						else
						{
							if (iinext != -1 && abs(tasks[inext][1] - elevators[i].getLevel()) > abs(tasks[iinext][0] - elevators[i].getLevel()))
							{
									elevators[i].task(tasks[iinext][0], tasks[inext][2]);
									tasks[iinext][0] = -1;
							}
							else
							{
								elevators[i].task(tasks[inext][1], tasks[inext][2]);
								tasks.erase(&tasks[inext][0]);
								elevators[i].delTask(inext);
							}
						}
					}*/
					/*for (auto j = tasks.begin(); j < tasks.end(); j++)
					{
						if ((*j)[3] == i && (elevators[i].getNext() - elevators[i].getLevel() == 0 || abs((*j)[0] - elevators[i].getLevel()) <= abs(elevators[i].getNext() - elevators[i].getLevel())))
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
					}*/
				}
			}
		}
	};
	void distribute()
	{
		int el = height*30, k, eln, icur, inex;
		vector<Task> itas;
		for (int i = 0; i < elevators.size(); i++)
		{
			t++;
			cout << i << " elev:  " << elevators[i].getLevel() << " -> ";
			if ((itas = elevators[i].getTasks()).empty())
			{
				cout << elevators[i].getNext() << '\n';
				if ((k = abs(elevators[i].getLevel() - tasks.back()[0])*10) < el)
				{
					eln = i;
					el = k;
					if (k == 0)
						break;
				}
			}
			else
			{
				for (auto j = itas.begin(); j < itas.end(); j++)
				{
					cout << (*j)[1] << " -> ";
					if (tasks.back()[0] <= max((*j)[0], (*j)[1]) && tasks.back()[0] >= min((*j)[0], (*j)[1]) && ((*j)[0] - (*j)[1])*(tasks.back()[0] - tasks.back()[1]) >= 0)
					{
						k = abs((*j)[0] - tasks.back()[0]);
						if (j != itas.begin())
							k += (*(j - 1))[4];
						if (k < el)
						{
							eln = i;
							el = k;
						}
						//break;					
					}
				}
				cout << '\n';
				if (!eln == i)
				{
					if ((k = itas.back()[4] + abs(itas.back()[1] - tasks.back()[0])*10 + 20) < el)
					{
						eln = i;
						el = k;
					}
				}
			}
			/*icur = elevators[i].getLevel();
			itas = elevators[i].getTasks();
			cout << i << " elev:  " << icur << " -> ";
			if (!itas.empty())
			{
				inex = itas.back()[1];
				for (auto j = itas.begin(); j < itas.end() - 1; j++)
					cout << (*j)[1] << " -> ";
			}
			else
				inex = elevators[i].getNext();
			cout << " " << inex << '\n';
			if ((icur == inex) && (k = abs(icur - tasks.back()[0])*10) < el)
			{
				eln = i;
				el = k;
				if (k == 0)
					break;
			}
			else
			{
				if (((icur - inex)*(tasks.back()[0] - tasks.back()[1]) > 0 && (k = abs(icur - tasks.back()[0])*10) + ((abs(icur - tasks.back()[0])*10 > abs(icur - inex)) ? 20 : 0) < el) || tasks.back()[0] == inex)
				{
					eln = i;
					el = k;
				}
				if (k == 0 || tasks.back()[0] == inex)
					break;
			}*/
		}
		tasks.back().appoint(eln);
		elevators[eln].addTask(tasks.back(), el);
	};
	void newTask(Task nt)
	{
		tnumber++;
		tasks.push_back(nt);
		tasks.back().setNumber(tnumber);
		cout << "added task #" << tnumber << ": from " << nt[0] << " level to " << nt[1] << " level" << '\n';
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
