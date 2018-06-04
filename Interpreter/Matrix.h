#pragma once
#include "Node.h"
#include <string>
#include <map>
#include <fstream>

using std::string;
using std::map;

const int MatrixRow = 7;
const int MatrixColumn = 9;

//####
bool isUnTerminate[256];
void buildIsUnTerminate()
{
	for (int i = 0; i < 256; i++)
		isUnTerminate[i] = false;
	isUnTerminate['S'] = true;
	isUnTerminate['A'] = true;
	isUnTerminate['E'] = true;
	isUnTerminate['T'] = true;
	isUnTerminate['P'] = true;
	isUnTerminate['M'] = true;
	isUnTerminate['L'] = true;
}

bool isTerminate[256];
void buildIsTerminate()
{
	for (int i = 0; i < 256; i++)
		isUnTerminate[i] = false;
	isTerminate['='] = true;
	isTerminate['('] = true;
	isTerminate[')'] = true;
	isTerminate['+'] = true;
	isTerminate['-'] = true;
	isTerminate['*'] = true;
	isTerminate['/'] = true;
}
//Value and Variable 记录为 false
//其余各个终结符号居委true
//####

string Matrix[MatrixRow][MatrixColumn];

map<char, string> charToString;
void buildCtoS()
{
	charToString['S'] = "S";
	charToString['A'] = "A";
	charToString['L'] = "L";
	charToString['E'] = "E";
	charToString['P'] = "P";
	charToString['='] = "=";
	charToString['T'] = "T";
	charToString['M'] = "M";
	charToString['('] = "(";
	charToString[')'] = ")";
	charToString['b'] = "value";
	charToString['+'] = "+";
	charToString['-'] = "-";
	charToString['*'] = "*";
	charToString['/'] = "/";
	charToString['c'] = "variable";
}

map<string, char> stringToChar;
void buildStoC()
{
	stringToChar["S"] = 'S';
	stringToChar["A"] = 'A';
	stringToChar["L"] = 'L';
	stringToChar["E"] = 'E';
	stringToChar["P"] = 'P';
	stringToChar["="] = '=';
	stringToChar["T"] = 'T';
	stringToChar["M"] = 'M';
	stringToChar["("] = '(';
	stringToChar[")"] = ')';
	stringToChar["b"] = 'b';
	stringToChar["+"] = '+';
	stringToChar["-"] = '-';
	stringToChar["*"] = '*';
	stringToChar["/"] = '/';
	stringToChar["c"] = 'c';
}

// Nodetype enum
// 行数
map<NodeType, int> nodeToInt;
void buildNodeToInt()
{
	nodeToInt[TEST_S] = 0;
	nodeToInt[TEST_A] = 1;
	nodeToInt[TEST_E] = 2;
	nodeToInt[TEST_T] = 3;
	nodeToInt[TEST_P] = 4;
	nodeToInt[TEST_M] = 5;
	nodeToInt[TEST_L] = 6;
}

map<int, NodeType> intToNode;
void buildIntToNode()
{
	intToNode[0] = TEST_S;
	intToNode[1] = TEST_A;
	intToNode[2] = TEST_E;
	intToNode[3] = TEST_T;
	intToNode[4] = TEST_P;
	intToNode[5] = TEST_M;
	intToNode[6] = TEST_L;
}

//####
map<char, NodeType> charToNode;
void buildCtoN()
{
	charToNode['S'] = TEST_S;
	charToNode['A'] = TEST_A;
	charToNode['E'] = TEST_E;
	charToNode['T'] = TEST_T;
	charToNode['P'] = TEST_P;
	charToNode['M'] = TEST_M;
	charToNode['L'] = TEST_L;
	charToNode['='] = EQUAL;
	charToNode['('] = LEFT_BRACKET;
	charToNode[')'] = RIGHT_BRACKET;
	charToNode['+'] = ADD;
	charToNode['-'] = MINUS;
	charToNode['*'] = MULTIPLY;
	charToNode['/'] = DIVIDE;
}

void buildMatrix();

// 列号
map<string, int> stringToInt;
void buildStringToInt()
{
	stringToInt["="] = 0;
	stringToInt["("] = 1;
	stringToInt[")"] = 2;
	stringToInt["b"] = 3;
	stringToInt["+"] = 4;
	stringToInt["-"] = 5;
	stringToInt["*"] = 6;
	stringToInt["/"] = 7;
	stringToInt["c"] = 8;
}
//####

void buildAll()
{
	buildCtoN();
	buildCtoS();
	buildIntToNode();
	buildIsTerminate();
	buildIsUnTerminate();
	buildNodeToInt();
	buildStoC();
	buildStringToInt();
	buildMatrix();
}
//####
//## def a func
//void calcMatrix()
//Usage: 将V'等转化为V-32/V-64待定
//####


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