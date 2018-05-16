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
			elevators[i].reduce();
			if (elevators[i].getLevel() != elevators[i].getNext())
			{
				if (counter[i] == 10)
				{
					elevators[i].changeLevel();
					counter[i] = 0;
					//if (!itasks.empty())
						//cout << i << "__" << itasks[0][4] << "     " << itasks[0][0] << "---" << itasks[0][1] << '\n';
				}
				else
				{
					counter[i]++;
					//cout << counter[i] << "__" << itasks[0][4] << "     " << itasks[0][1] << "---" << itasks[0][2] << '\n';
				}
			}
			else
			{
				if (!itasks.empty())
				{
					if (counter[i] == 20)
					{
						elevators[i].exit();
						counter[i] = 0;
						elevators[i].task();
					}
					else
						counter[i]++;
				}
			}
		}
	};
	void distribute()
	{
		int el = height*30, k, eln, icur, inex, red = 0, flag = 0;
		vector<Task> itas;
		for (int i = 0; i < elevators.size(); i++)
		{
			red++;
			iteration();
			cout << i << " elevator:  " << elevators[i].getLevel() << " -> ";
			//cout << i << " elevator:  " << elevators[i].getLevel();
			if ((itas = elevators[i].getTasks()).empty())
			{
				cout << elevators[i].getNext() << '\n';
				if ((k = abs(elevators[i].getLevel() - tasks.back()[0])*10) < el)
				{
					eln = i;
					el = k;
					flag = 0;
					if (k == 0)
						break;
				}
				cout << " .k = " << k << '\n';
			}
			else
			{
				for (auto j = itas.begin(); j < itas.end(); j++)
				{
					iteration();
					red++;
					cout << (*j)[1] << ((j == itas.end() - 1) ? "" : " -> ");
					if (tasks.back()[0] <= max((*j)[0], (*j)[1]) && tasks.back()[0] >= min((*j)[0], (*j)[1]) && ((*j)[0] - (*j)[1])*(tasks.back()[0] - tasks.back()[1]) >= 0 && !(j == itas.begin() && tasks.back()[0] == (*j)[0]))
					{
						iteration();
						red++;
						if (j == itas.end() - 1 || (tasks.back()[1] <= max((*j)[0], (*j)[1]) && tasks.back()[1] >= min((*j)[0], (*j)[1])) ||  ((*(j + 1))[0] - (*(j + 1))[1])*(tasks.back()[0] - tasks.back()[1]) >= 0)
						{
							k = abs((*j)[0] - tasks.back()[0])*10;
							if (j != itas.begin())
								k += (*(j - 1))[4];
							if (k < el)
							{
								eln = i;
								el = k;
								cout << " k = " << k << '\n';
								red = 0; flag = 1;
								break;	
							}
							else
								break;
						}				
					}
				}
				if (el <= 10 + elevators.size())
					break;
				cout << '\n';
				iteration();
				red++;
				if (eln != i && (k = itas.back()[4] + abs(itas.back()[1] - tasks.back()[0])*10 + 20) < el)
				{
					eln = i;
					el = k;
					cout << " k = " << k << '\n';
					red = 0; flag = 1;
				}
			}
		}
		tasks.back().appoint(eln);
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
