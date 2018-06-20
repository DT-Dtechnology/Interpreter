#include "Matrix.h"
#include <fstream>
#include <iostream>

using std::ifstream;
using std::cout;
using std::endl;

void buildMatrix()
{
	ifstream fin;
	fin.open("009.txt");
	char c;
	string str = "";
	int row = 0, column = 0;
	while (fin >> c)
	{
		if (c == '\n')
		{
			row++;
			column = 0;
			continue;
		}
		if (c == '|')
		{
			if (str != "")
			{
				Matrix[row][column] = str;
				str = "";
				column++;
			}
		}
		else
		{
			str = str + c;
		}
	}
	fin.close();
}

void printMatrix()
{
	for (int i = 0; i < MatrixRow; i++)
	{
		for (int j = 0; j < MatrixColumn; j++)
			cout << Matrix[i][j] << " ";
		cout << endl;
	}
}
