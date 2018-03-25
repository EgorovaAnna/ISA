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
public:
	Package(int a, int b, int c);
	int getA();
	int getB();
	int getC();
	int getSum();
	float getAlg1(Package prev);
	float getAlg2(Package prev);
	float getAlg3(Package prev);
};
Package::Package(int a, int b, int c)
{
	mas[0] = a;
	mas[1] = b;
	mas[2] = c;
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
float Package::getAlg1(Package prev)
{
	return (getA() - prev.getA() + getB() - prev.getB());
}
float Package::getAlg2(Package prev)
{
	return (getA() - prev.getA() + getB() - prev.getB())/getC();
}
float Package::getAlg3(Package prev)
{
	return (100 + getA() - prev.getA() + getB() - prev.getB())/getC();
}

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
	void getPos(int mas[10]);
	float getAlg1(int pos, int posPr);
	float getAlg2(int pos, int posPr);
	int alg1();
	int alg2();
	int alg3();
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
	return masp[pos] -> getSum();
}
void MasPack::getPos(int &mas[10])
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
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(masp[i] -> getSum() < sum)
		{
			sum = masp[i] -> getSum();
			a = i;
		}
	}
	mas[0] = a;
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		count = masp[i + 1] -> getAlg1(*masp[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(masp[j] -> getAlg1(*masp[i]) < count)
			{
				a = j;
				count = masp[j] -> getAlg1(*masp[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 1; i < 10; i++)
	{
		position[i] = mas[i];
	}
	cout << countTime() << "\n";
	return countTime();
}
int MasPack::alg2()
{
	int a = 0, b, c, sum, i, j, t;
	float count;
	int mas[10];
	sum = getSum(0);
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(masp[i] -> getSum() < sum)
		{
			sum = masp[i] -> getSum();
			a = i;
		}
	}
	mas[0] = a;
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		count = masp[i + 1] -> getAlg3(*masp[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(masp[j] -> getAlg3(*masp[i]) < count)
			{
				a = j;
				masp[j] -> getAlg3(*masp[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 1; i < 10; i++)
	{
		position[i] = mas[i];
	}
	cout << countTime() << "\n";
	return countTime();
}
int MasPack::alg3()
{
	int a = 0, b, c, sum, i, j, t;
	float count;
	int mas[10];
	sum = getSum(0);
	for(i = 1; i < 10; i++)
	{
		mas[i] = position[i];
		if(masp[i] -> getSum() < sum)
		{
			sum = masp[i] -> getSum();
			a = i;
		}
	}
	mas[0] = a;
	mas[a] = position[0];
	for(i = 0; i < 8; i++)
	{
		count = masp[i + 1] -> getAlg2(*masp[i]);
		for(j = i + 2; j < 10; j++)
		{
			if(masp[j] -> getAlg2(*masp[i]) < count)
			{
				a = j;
				masp[j] -> getAlg2(*masp[i]);
			}
		}
		b = mas[i + 1];
		mas[i + 1] = mas[a];
		mas[a] = b;
	}
	for(i = 1; i < 10; i++)
	{
		position[i] = mas[i];
	}
	cout << countTime() << "\n";
	return countTime();
}
MasPack::~MasPack()
{
	int i;
	for(i = 0; i < 10; i++)
		delete masp[i];
}

void numbers()
{
	int j, a, b, sum, k;
	unsigned long int i;
	int mas[10];
	ofstream fout("numbers.txt");
	for(i = 1023456789; i <= 8976543210; i++)
	//for(i = 1023456789; i < 1276543210; i++)
	{
		sum = 0;
		b = 0;
		a = 0;
		if ( i == 1023456789)
			cout << "0_0\n";
		for(j = 9; j > -1; j--)
		{
			mas[j] = (i % (int)(pow(10, 10 - j)) - b)/(int)pow(10, 9 - j);
			if(j < 9)
			{
				for(k = j + 1; k < 10; k ++)
				{
					if(mas[j] == mas[k])
						a = 10;
				}
			}
			if(a == 10)
				break;
			b = i % (int)pow(10, 10 - j);
			sum += mas[j];
		}
		if ((sum == 45)&&(a != 10))
		{
			for(k = 0; k < 10; k++)
				fout << mas[k] << " ";
			fout << "\n";
			if(mas[9] == 0)
			{
				fout << 0 << " ";
				for(k = 0; k < 9; k++)
					fout << mas[k] << " ";
				fout << "\n";
				if(mas[8] == 9)
				{
					fout << 9 << " " << 0 << " ";
					for(k = 0; k < 8; k++)
						fout << mas[k] << " ";
					fout << "\n";
				}
			}
			if(mas[9] == 9)
			{
				fout << 9 << " ";
				for(k = 0; k < 9; k++)
					fout << mas[k] << " ";
				fout << "\n";
			}
		}
	}
}
void numbers1()
{
	int a, b, c, d, e, f, j, h, i, k;
	int mas[10];
	ofstream fout("numbers.txt");
	for(a = 0; a < 10; a++)
	{
		mas[0] = a;
		for(b = 0; b < 10; b++)
		{
			if(b != a)
			{
				mas[1] = b;
				for(c = 0; c < 10; c++)
				{
					if((c != a)&&(c != b))
					{
						mas[2] = c;
						for(d = 0; d < 10; d++)
						{
							if((d != a)&&(d != b)&&(d != c))
							{
								mas[3] = d;
								for(e = 0; e < 10; e++)
								{
									if((e != a)&&(e != b)&&(e != c)&&(e != d))
									{
										mas[4] = e;
										for(f = 0; f < 10; f++)
										{
											if((f != a)&&(f != b)&&(f != c)&&(f != d)&&(f != e))
											{
												mas[5] = f;
												for(j = 0; j < 10; j++)
												{
													if((j != a)&&(j != b)&&(j != c)&&(j != d)&&(j != e)&&(j != f))
													{
														mas[6] = j;
														for(h = 0; h < 10; h++)
														{
															if((h != a)&&(h != b)&&(h != c)&&(h != d)&&(h != e)&&(h != f)&&(h != j))
															{
																mas[7] = h;
																for(i = 0; i < 10; i++)
																{
																	if((i != a)&&(i != b)&&(i != c)&&(i != d)&&(i != e)&&(i != f)&&(i != j)&&(i != h))
																	{
																		mas[8] = i;
																		for(k = 0; k < 10; k++)
																		{
																			if((k != a)&&(k != b)&&(k != c)&&(k != d)&&(k != e)&&(k != f)&&(k != j)&&(k != h)&&(k != i))
																			{
																				mas[9] = k;
																			}
																			fout << mas[k] << " ";
																		}
																		fout << "\n";
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}



int main()
{
	int a, b, c, i, t, tmin, tmax = 0;
	int mas[10];
	MasPack masp;
	//numbers1();
	ifstream fin("mat.txt");
	ifstream numin("numbers.txt");
	for(i = 0; i < 10; i++)
	{
		fin >> a >> b >> c;
		masp.setPack(a, b, c);
	}
	tmin = masp.countTime();
	//cout << masp.countTime() << "\n";
	while(!numin.eof())
	{
		for(i = 0; i < 10; i++)
			numin >> mas[i];
		masp.setPos(mas);
		t = masp.countTime();
		if (t < tmin)
		{
			tmin = t;
			masp.getPos(mas);
		}
		if(t > tmax)
			tmax = t;
		//cout << t << "     ";
		//if(i % 20 == 0)
		//	cout << "\n";
	}
	//cout << masp.countTime();
	cout << "\nTmin = " << tmin << "    \nTmax = " << tmax << "\n\nTopt = ";
	masp.alg1();
	masp.alg2();
	masp.alg3();
		
		
		
		
}