#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

class Task
{
	int from, to, people, elevator, tnumber;
public:
	Task(int a, int b, int c = 1, int num = 0)
	{
		from = a; to = b; people = c; elevator = -1; tnumber = num;
	};
	int & operator[](int a)
	{
		if (a == 0)
			return from;
		if (a == 1)
			return to;
		if (a == 2)
			return people;
		if (a == 3)
			return elevator;
		return tnumber;
	};
	void appoint(int el)
	{
		elevator = el;
		cout << "task #" << tnumber << " appoint to elevator #" << elevator << '\n' << '\n' << '\n';
	};
	void setNumber(int tn)
	{
		tnumber = tn;
	};
};
