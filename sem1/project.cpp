#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include "masPack.cpp"

using namespace std;

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
	int a, b, c, i, j, t, tmin, tmax = 0;
	int mas[10], masmas[100][6], koef[4];
	MasPack masp[100];
	//numbers1();
	ifstream numin;
	ifstream fin;
	for(j = 0; j < 100; j++)
	{
		tmax = 0;
		numin.open("numbers.txt");
		system("./mm");
		fin.open("mat.txt");
		for(i = 0; i < 10; i++)
		{
			fin >> a >> b >> c;
			masp[j].setPack(a, b, c);
		}
		tmin = masp[j].countTime();
		while(!numin.eof())
		{
			for(i = 0; i < 10; i++)
				numin >> mas[i];
			masp[j].setPos(mas);
			t = masp[j].countTime();
			if (t < tmin)
			{
				tmin = t;
				//masp[j].getPos(mas);
			}
			if(t > tmax)
				tmax = t;
		}
		//cout << "\nTmin = " << tmin << "    Tmax = " << tmax << "  Topt = ";
		masmas[j][0] = tmin;
		masmas[j][1] = tmax;
		masmas[j][2] = masp[j].alg1();
		masmas[j][3] = masp[j].alg2();
		masmas[j][4] = masp[j].alg3();
		//masmas[j][5] = masp[j].alg4();
		koef[0] += masmas[j][2] - masmas[j][0];
		koef[1] += masmas[j][3] - masmas[j][0];
		koef[2] += masmas[j][4] - masmas[j][0];
		//koef[3] += masmas[j][5] - masmas[j][0];
		cout << "\n";
		fin.close();
		numin.close();
	}
	cout << koef[0] << " " << koef[1] << " " << koef[2] << "\n";
		
		
		
		
}