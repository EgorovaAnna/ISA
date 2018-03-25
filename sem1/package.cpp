#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class Package
{
	int mas[3];
	int sum;
	int maxSum;
public:
	Package(int a, int b, int c);
	int getA();
	int getB();
	int getC();
	int getSum();
	void setMaxSum(int ms);
	float getAlg1(Package prev);
	float getAlg2(Package prev);
	float getAlg3(Package prev);
	float getAlg4(Package prev);
};
Package::Package(int a, int b, int c)
{
	mas[0] = a;
	mas[1] = b;
	mas[2] = c;
	maxSum = getSum();
}
int Package::getA()
{
	return mas[0];
}
int Package::getB()
{
	return mas[1];
}
int Package::getC()
{
	return mas[2];
}
int Package::getSum()
{
	return (mas[0] + mas[1]);
}
void Package::setMaxSum(int ms)
{
	maxSum = ms;
}
float Package::getAlg1(Package prev)
{
	return (float)(getA() - prev.getA() + getB() - prev.getB());
}
float Package::getAlg2(Package prev)
{
	return (float)(getA() - prev.getA() + getB() - prev.getB())/getC();
}
float Package::getAlg3(Package prev)
{
	return (float)(maxSum + getA() - prev.getA() + getB() - prev.getB())/getC();
}
float Package::getAlg4(Package prev)
{
	return (float)(getA() - prev.getA() + getB() - prev.getB())*(getA())/getC();
}