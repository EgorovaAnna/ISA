#include "Task.h"

Task::Task(int a, int b, int c, int num)
{
	from = a; to = b; people = c; elevator = -1; tnumber = num;
};
int & Task::operator[](int a)
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
void Task::appoint(int el, int t)
{
	elevator = el;
	cout << "task #" << tnumber << " appoint to elevator #" << elevator + 1 << ", it taked " << t << " moments" << '\n' << '\n' << '\n';
};
void Task::setNumber(int tn)
{
	tnumber = tn;
};
bool Task::operator()(Task &a, Task &b)
{
	return a[0] > b[0];
};
