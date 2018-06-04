#pragma once
#include "Node.h"
#include <string>
#include <map>

using std::string;
using std::map;

const int MatrixRow = 7;
const int MatrixColumn = 9;

//####
bool isUnTerminate[256];
bool isTerminate[256];
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
	stringToChar["value"] = 'b';
	stringToChar["+"] = '+';
	stringToChar["-"] = '-';
	stringToChar["*"] = '*';
	stringToChar["/"] = '/';
	stringToChar["variable"] = 'c';
}

// Nodetype enum
map<NodeType, int> nodeToInt;

map<int, NodeType> intToNode;

//####
map<char, NodeType> charToNode;
map<string, int> stringToInt;
//####

//####
//## def a func
//void calcMatrix()
//Usage: 将V'等转化为V-32/V-64待定
//####