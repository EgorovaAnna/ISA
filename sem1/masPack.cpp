#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "package.cpp"

using namespace std;

class MasPack
{
	Package *masp[10];
	int position[10];
	int count;
public:
	MasPack();
	void setPack(int a, int b, int c);
	void setPos(int pos[10]);
	int getSum(int pos);
	void setMaxSum(int ms);
	void getPos(int *mas);
	float getAlg1(int pos, int posPr);
	float getAlg2(int pos, int posPr);
	float getAlg3(int pos, int posPr);
	float getAlg4(int pos, int posPr);
	int alg1();
	int alg2();
	int alg3();
	int alg4();
	int countTime();
	~MasPack();
};
MasPack::MasPack()
{
	int i;
	count = 0;
	for(i = 0; i < 10; i++)
		position[i] = i;
}
void MasPack::setPack(int a, int b, int c)
{
	masp[count] = new Package(a, b, c);
	count++;
}
void MasPack::setPos(int pos[10])
{
	int i;
	for(i = 0; i < 10; i++)
		position[i] = pos[i];
}
int MasPack::getSum(int pos)
{
	return masp[position[pos]] -> getSum();
}
void MasPack::setMaxSum(int ms)
{
	for(int i = 0; i < count; i++)
		masp[position[i]] -> setMaxSum(ms);
}
void MasPack::getPos(int *mas)
{
	int i;
	for(i = 0; i < 10; i++)
		mas[i] = position[i];
}
float MasPack::getAlg1(int pos, int posPr)
{
	return masp[pos] -> getAlg1(*masp[posPr]);
}
float MasPack::getAlg2(int pos, int posPr)
{
	return masp[pos] -> getAlg2(*masp[posPr]);
}
float MasPack::getAlg3(int pos, int posPr)
{
	return masp[pos] -> getAlg3(*masp[posPr]);
}
float MasPack::getAlg4(int pos, int posPr)
{
	return masp[pos] -> getAlg4(*masp[posPr]);
}
int MasPack::countTime()
{
	int i, j, t1 = 0, t2 = 0, t3 = 0;
	for(i = 0; i < 10; i++)
	{
		t1 += (*masp[position[i]]).getA();
		if (t1 > t2)
			t2 = t1;
		t2 += (*masp[position[i]]).getB();
		if (t2 > t3)
			t3 = t2;
		t3 += (*masp[position[i]]).getC();
	}
	return t3;
}
int MasPack::alg1()
{
	int a = 0, b, c, sum, i, j, t;
	float count;
	int mas[10];
	sum = getSum(0);
	mas[0] = position[0];
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(getSum(i) < sum)
		{
			sum = getSum(i);
			a = i;
		}
	}
	mas[0] = position[a];
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		a = i + 1;
		count = getAlg1(mas[i + 1], mas[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(getAlg1(mas[j], mas[i]) < count)
			{
				a = j;
				count = getAlg1(mas[j], mas[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 0; i < 10; i++)
	{
		position[i] = mas[i];
		//cout << mas[i] << " ";
	}
	//cout << "\n"; 
	cout << countTime() << " ";// "\n";
	return countTime();
}
int MasPack::alg2()
{
	int a = 0, b, c, sum, i, j, t;
	float count;
	int mas[10];
	sum = getSum(0);
	mas[a] = position[0];
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(getSum(i) < sum)
		{
			sum = getSum(i);
			a = i;
		}
	}
	mas[0] = position[a];
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		a = i + 1;
		count = getAlg2(mas[i + 1], mas[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(getAlg2(mas[j], mas[i]) < count)
			{
				a = j;
				count = getAlg2(mas[j], mas[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 0; i < 10; i++)
	{
		position[i] = mas[i];
		//cout << mas[i] << " ";
	}
	//cout << "\n"; 
	cout << countTime() << " ";// "\n";
	return countTime();
}
int MasPack::alg3()
{
	int a = 0, b, sum, ms, i, j;
	float count;
	int mas[10];
	sum = getSum(0);
	ms = sum;
	mas[a] = position[0];
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(getSum(i) < sum)
		{
			sum = getSum(i);
			a = i;
		}
		if(getSum(i) > ms)
			ms = getSum(i);
	}
	setMaxSum(ms);
	mas[0] = position[a];
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		a = i + 1;
		count = getAlg3(mas[i + 1], mas[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(getAlg3(mas[j], mas[i]) < count)
			{
				a = j;
				count = getAlg3(mas[j], mas[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 0; i < 10; i++)
	{
		position[i] = mas[i];
		//cout << mas[i] << " ";
	}
	//cout << "\n"; 
	cout << countTime() << " ";// "\n";
	return countTime();
}
int MasPack::alg4()
{
	int a = 0, b, sum, i, j;
	float count;
	int mas[10];
	sum = getSum(0);
	mas[a] = position[0];
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(getSum(i) < sum)
		{
			sum = getSum(i);
			a = i;
		}
	}
	mas[0] = position[a];
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		a = i + 1;
		count = getAlg4(mas[i + 1], mas[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(getAlg4(mas[j], mas[i]) < count)
			{
				a = j;
				count = getAlg4(mas[j], mas[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 0; i < 10; i++)
	{
		position[i] = mas[i];
		//cout << mas[i] << " ";
	}
	//cout << "\n"; 
	cout << countTime() << " ";// "\n";
	return countTime();
}
MasPack::~MasPack()
{
	int i;
	for(i = 0; i < 10; i++)
		delete masp[i];
}