#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <algorithm>

using namespace std;

class Task
{
	int from, to, people, elevator, tnumber;
public:
	Task(int a, int b, int c = 1, int num = 0);
	int & operator[](int a);
	void appoint(int el, int t);
	void setNumber(int tn);
	bool operator()(Task &a, Task &b);
};
