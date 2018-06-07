﻿#pragma once
#include "Node.h"
#include <string>
#include <map>
#include <fstream>
#include "InputHelper.h"

//####

using std::string;
using std::map;
using std::getline;

const int MatrixRow = 27;
const int MatrixColumn = 31;

//####
bool isUnTerminate[256];
bool isTerminate[256];

string Matrix[MatrixRow][MatrixColumn];

// 非终结符对应的行号
// eg: SEN
map<NodeType, int> nodeToInt;
map<char, NodeType> charToNode;
map<string, char> stringToChar;
map<char, string> charToString;
// 终结符对应的列号
// eg: ==
map<string, int> stringToInt;
map<string, NodeType> stringToNode;
// test用
map<NodeType, string> nodeToString;

void buildMaps()
{
	InputHelper::help_input();
	stringToChar = InputHelper::Map;
	stringToChar["#"] = '#';
	for(auto it = stringToChar.begin();it!=stringToChar.end();++it)
	{
		charToString[it->second] = it->first;
		charToNode[it->second] = stringToNode[charToString[it->second]];
	}	

}

void buildMatrix();

void buildStoN()
{
	string set1[] = { "SEN", "LOOP", "IF", "EXP", "JUMP", "DEF", "PRINT", "ASS",
		"T", "E'", "F", "T'", "G", "F'", "H", "G'", "K", "H'", "X",
		"FUNC", "PARAL", "PARA", "PARAL'", "var", "VARL'", "VARL", "EXPL", "EXPL'",
		"while", ":", "for", "in", "if", "elif", "else", ",", "~", "==", "!=", "<<",
		">>", "+", "-", "*", "/", "not", "(", ")", "continue", "break", "pass", "return",
		"def", "=", "print" };
	NodeType set2[] = { SEN, LOOP, IF, EXP, JUMP, DEF, PRINT, ASS,
		T, EE, F, TT, G, FF, H, GG, K, HH, X, FUNC, PARAL, PARA, PARALL, VARIABLE, VARLL,
		VARL, EXPL, EXPLL, WHILE, COLON, FOR, IN, IF, ELIF, ELSE, COMMA, TERMINATE, IS_EQUAL,
		IS_NOT_EQUAL, LEFT_MOVE, RIGHT_MOVE, ADD, MINUS, MULTIPLY, DIVIDE, NOT, LEFT_BRACKET,
		RIGHT_BRACKET, CONTINUE, BREAK, PASS, RETURN, DEFF, EQUAL, PRINTT };
	for (int i = 0; i < 55; i++)
	{
		stringToNode[set1[i]] = set2[i];
		nodeToString[set2[i]] = set1[i];
	}
		
}

void testIsTer();
void testBoolMap();
void testStoI();
void testNtoI();
void testCtoN();

void buildAll()
{
	buildStoN();
	buildMaps();
	buildMatrix();
	testBoolMap();
	testStoI();
	testNtoI();
	testCtoN();
}

void buildMatrix()
{
	ifstream fin;
	fin.open("InputTable.txt");
	// charToColumn
	string line;
	getline(fin, line);
	getline(fin, line);
	int column = 0;

	for (int i = 0; i < 256; i++)
	{
		isUnTerminate[i] = false;
		isTerminate[i] = false;
	}

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != '|' && line[i] != '\'')
		{
			if (line[i + 1] != '\'')
			{
					stringToInt[charToString[line[i]]] = column;
				if (charToNode[line[i]] != VARIABLE)
				{
					isTerminate[line[i]] = true;
				}
				column++;
			}
			else
			{
				stringToInt[charToString[line[i] - 64]] = column;
				if (charToNode[line[i] - 64] != VARIABLE)
				{
					isTerminate[line[i] - 64] = true;
				}
				column++;
				i++;
			}
		}
	}
	getline(fin, line);
	for (int row = 0; row < MatrixRow; row++)
	{
		column = 0;
		getline(fin, line);
		string str = "";
		// stringToRow
		int head;
		for (head = 0; head < line.length(); head++)
		{
			if (line[head] != '|')
			{
				if (line[head + 1] != '\'')
				{
					nodeToInt[charToNode[line[head]]] = row;
					isUnTerminate[line[head]] = true;
					break;
				}
				else
				{
					nodeToInt[charToNode[line[head] - 64]] = row;
					isUnTerminate[line[head] - 64] = true;
					head++;
					break;
				}
			}
		}
		// matrix
		for (int j = head + 1; j < line.length(); j++)
		{
			if (line[j] == '\'')
			{
				str[str.length() - 1] -= 64;
				continue;
			}
			if (line[j] == '|')
			{
				if (str != "")
				{
					//cout << "ok" << endl;
					Matrix[row][column] = str;
					str = "";
					column++;
				}
			}
			else
				str = str + line[j];
		}
		getline(fin, line);
	}
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

// test
void testBoolMap()
{
	cout << "isUnTerminate test\n";
	for (int i = 0; i < 128; i++)
		cout << char(i) << " " << isUnTerminate[i] << endl;
	cout << endl;
	cout << "isTerminate test\n";
	for (int i = 0; i < 128; i++)
		cout << char(i) << " " << isTerminate[i] << endl;
}

void testStoI()
{
	for (auto it = stringToInt.begin(); it != stringToInt.end(); it++)
		cout << it->first << " " << it->second << endl;
	system("pause");
	for (auto it = stringToChar.begin(); it != stringToChar.end(); ++it)
		cout << it->first << " " << it->second << endl;
	system("pause");
}

void testNtoI()
{
	for (auto it = nodeToInt.begin(); it != nodeToInt.end(); it++)
		cout << it->first << " " << it->second << endl;
}

void testCtoN()
{
	for (auto it = charToNode.begin(); it != charToNode.end(); it++)
		cout << it->first << " " << nodeToString[it->second] << endl;
}