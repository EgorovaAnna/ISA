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
		for (int i = 0; i < elevators.size(); i++)
		{
			itasks = elevators[i].getTasks();
			if (elevators[i].reduce() < 0)
				counter[i] = 0;
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
				if (!itasks.empty())
				{
					if (counter[i] == 20 || elevators[i].getCounter() == 0)
					{
						//cout << "exit " << i << '\n';
						elevators[i].exit();
						counter[i] = 0;
						elevators[i].task(true);
						//elevators[i].recount();
					}
					else
						counter[i]++;
				}
			}
		}
	};
	void distribute()
	{
		int el = height*30, k, eln, icur, inex, red = 0, flag = 0, tt = 0;
		vector<Task> itas;
		for (int i = 0; i < elevators.size(); i++)
		{
			red++;
			iteration();
			tt++;
			cout << i << " elevator:  " << elevators[i].getLevel();
			if ((itas = elevators[i].getTasks()).empty())
			{
				cout << '\n';
				if ((k = abs(elevators[i].getLevel() - tasks.back()[0])*10) < el)
				{
					eln = i;
					el = k;
					flag = 0;
					if (k == 0)
						break;
				}
			}
			else
			{
				for (auto j = itas.begin(); j < itas.end(); j++)
				{
					iteration();
					tt++;
					red++;
					cout  << " -> " << (*j)[1];
					if (tasks.back()[0] <= max((*j)[0], (*j)[1]) && tasks.back()[0] >= min((*j)[0], (*j)[1]) && ((*j)[0] - (*j)[1])*(tasks.back()[0] - tasks.back()[1]) >= 0 && !(j == itas.begin() && tasks.back()[0] == (*j)[0]))
					{
						iteration();
						tt++;
						red++;
						if (j == itas.end() - 1 || (tasks.back()[1] <= max((*j)[0], (*j)[1]) && tasks.back()[1] >= min((*j)[0], (*j)[1])) ||  ((*(j + 1))[0] - (*(j + 1))[1])*(tasks.back()[0] - tasks.back()[1]) >= 0)
						{
							k = abs((*j)[0] - tasks.back()[0])*10;
							if (j != itas.begin())
								k += (*(j - 1))[4];
							if (k < el && k >10)
							{
								eln = i;
								el = k;
								red = 0; flag = 1;
							}
							break;
						}				
					}
				}
				cout << '\n';
				if (el <= 10 + elevators.size() && flag == 1)
					break;
				iteration();
				tt++;
				red++;
				if (eln != i && (k = itas.back()[4] + abs(itas.back()[1] - tasks.back()[0])*10 + 20) < el)
				{
					eln = i;
					el = k;
					red = 0; flag = 1;
				}
			}
		}
		tasks.back().appoint(eln, tt);
		if (flag == 1)
			el -= red;
		elevators[eln].addTask(tasks.back(), el);
	};
	void newTask(Task nt)
	{
		if(nt[0] != nt[1])
		{
			tnumber++;
			tasks.push_back(nt);
			tasks.back().setNumber(tnumber);
			cout << "At moment " << t << " added task #" << tnumber << ": from " << nt[0] << " level to " << nt[1] << " level" << '\n';
			distribute();
		}
	};
	void newTasks(vector<Task> nt)
	{
		for (auto i = nt.begin(); i < nt.end(); i++)
		{
			if((*i)[0] != (*i)[1])
			{
				tnumber++;
				cout << "At moment " << t << " added task #" << tnumber << ": from " << (*i)[0] << " level to " << (*i)[1] << " level" << '\n';
			}
			else
				nt.erase(i);
		}
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
			if (!elevators[i].getTasks().empty() || counter[i] != 0)
				return false;
		return true;
	};
};
