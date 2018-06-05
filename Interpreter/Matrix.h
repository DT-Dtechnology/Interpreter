#pragma once
#include "Node.h"
#include <string>
#include <map>
#include <fstream>

using std::string;
using std::map;

const int MatrixRow = 7;
const int MatrixColumn = 10;

//####
bool isUnTerminate[256];
void buildIsUnTerminate()
{
	for (int i = 0; i < 256; i++)
		isUnTerminate[i] = false;
	char UTsets[] = { 'A', 'L', 'E', 'T', 'G', 'H', 'F' };
		for (auto i : UTsets) {
			isUnTerminate[(int)i] = true;
		}
}

bool isTerminate[256];
void buildIsTerminate()
{
	for (int i = 0; i < 256; i++)
		isUnTerminate[i] = false;
	//= ~ ( ) b c + - * / 
	char Tsets[] = { '=', '(', ')', '+', '-', '*', '/' , '#'};
	for (auto i : Tsets) {
		isTerminate[(int)i] = true;
	}
}
//Value and Variable 记录为 false
//其余各个终结符号居委true
//####

string Matrix[MatrixRow][MatrixColumn];

//map<char, string> charToString;
/*void buildCtoS()
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
}*/

map<string, char> stringToChar;
void buildStoC()
{
	string UTsets[] = { "A", "L", "E", "T", "G", "H", "F" };
	char UTsetc[] = { 'A', 'L', 'E', 'T', 'G', 'H', 'F' };
	for (int i = 0; i < MatrixRow; i++) {
		stringToChar[UTsets[i]] = UTsetc[i];
		}
	string Tsets[] = { "=", "#", "(", ")", "b", "c", "+", "-", "*", "/" };
	char Tsetc[] = { '=', '#', '(', ')', 'b', 'c', '+', '-', '*', '/' };
	for (int i = 0; i < MatrixColumn; i++) {
		stringToChar[Tsets[i]] = Tsetc[i];
	}
}

// Nodetype enum
// 行数
map<NodeType, int> nodeToInt;
void buildNtoI()
{
	nodeToInt[TEST_A] = 0;
	nodeToInt[TEST_E] = 1;
	nodeToInt[TEST_G] = 2;
	nodeToInt[TEST_T] = 3;
	nodeToInt[TEST_H] = 4;
	nodeToInt[TEST_F] = 5;
	nodeToInt[TEST_L] = 6;
}

//map<int, NodeType> intToNode;
/*void buildIntToNode()
{
	intToNode[0] = TEST_S;
	intToNode[1] = TEST_A;
	intToNode[2] = TEST_E;
	intToNode[3] = TEST_T;
	intToNode[4] = TEST_P;
	intToNode[5] = TEST_M;
	intToNode[6] = TEST_L;
}*/

//####
map<char, NodeType> charToNode;
void buildCtoN()
{
	//'A', 'L', 'E', 'T', 'G', 'H', 'F', 'P', 'M'
	charToNode['A'] = TEST_A;
	charToNode['L'] = TEST_L;
	charToNode['E'] = TEST_E;
	charToNode['T'] = TEST_T;
	charToNode['G'] = TEST_G;
	charToNode['H'] = TEST_H;
	charToNode['F'] = TEST_F;
	charToNode['P'] = TEST_P;
	charToNode['M'] = TEST_M;
	//'=', '#', '(', ')', 'b', 'c', '+', '-', '*', '/'
	charToNode['='] = EQUAL;
	charToNode['('] = LEFT_BRACKET;
	charToNode[')'] = RIGHT_BRACKET;
	charToNode['+'] = ADD;
	charToNode['-'] = MINUS;
	charToNode['*'] = MULTIPLY;
	charToNode['/'] = DIVIDE;
	charToNode['#'] = END;
}
void buildMatrix();

// 列号
map<string, int> stringToInt;
void buildStoI()
{
	stringToInt["="] = 0;
	stringToInt["+"] = 1;
	stringToInt["-"] = 2;
	stringToInt["#"] = 3;
	stringToInt["*"] = 4;
	stringToInt["/"] = 5;
	stringToInt["("] = 6;
	stringToInt[")"] = 7;
	stringToInt["b"] = 8;
	stringToInt["c"] = 9;
}
//####

void buildAll()
{
	buildCtoN();
	buildIsTerminate();
	buildIsUnTerminate();
	buildNtoI();
	buildStoC();
	buildStoI();
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
	fin.open("table.txt");
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