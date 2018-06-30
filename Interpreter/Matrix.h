#pragma once
#include "Node.h"
#include <string>
#include <map>
#include <fstream>
#include "InputHelper.h"

/*
 * 
 * 该文件的作用生成所需要的全部矩阵、映射等信息。只是程序运行的数据基础。
 */

using std::string;
using std::map;
using std::getline;

const int MatrixRow = 27;
const int MatrixColumn = 39;

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
void buildisOper();

void buildStoN()
{
	string set1[] = { "SEN", "LOOP", "IF", "EXP", "JUMP", "DEF", "PRINT", "ASS",
		"T", "E'", "F", "T'", "G", "F'", "H", "G'", "K", "H'", "X", "MI", "L",
		"FUNC", "PARAL", "PARA", "PARAL'", "var", "VARL'", "VARL", "EXPL", "EXPL'",
		"while", ":", "for", "in", "if", "elif", "else", ",", "#", "==", "!=", "<<",
		">>", "+", "-", "*", "/", "not", "(", ")", "continue", "break", "pass", "return",
		"def", "=", "print", "Z" , "Z'", "M", "N", "O", "M'", "N'", "O'", ">", "<", ">=", "<=", "and"
		, "or", "&", "|", "^", "%", "//", "posi", "nega"};
	NodeType set2[] = { SEN, LOOP, IF, EXP, JUMP, DEF, PRINT, ASS,
		T, EE, F, TT, G, FF, H, GG, K, HH, X, MI, L, FUNC, PARAL, PARA, PARALL, VARIABLE, VARLL,
		VARL, EXPL, EXPLL, WHILE, COLON, FOR, IN, IF, ELIF, ELSE, LISTFLAG, END, IS_EQUAL,
		IS_NOT_EQUAL, LEFT_MOVE, RIGHT_MOVE, ADD, MINUS, MULTIPLY, DIVIDE, NOT, LEFT_BRACKET,
		RIGHT_BRACKET, CONTINUE, BREAK, PASS, RETURN, DEFF, EQUAL, PRINTT, Z, ZZ, M, N, O ,MM, NN, OO,
		BIGGER, SMALLER, BIGGER_OR_EQUAL, SMALLER_OR_EQUAL, AND, OR, WEI_AND, WEI_OR, WEI_YIHUO,
		MOD, ZHENG_DIVIDE, POSI, NEGA };
	for (int i = 0; i < sizeof(set2)/sizeof(Z); i++)
	{
		stringToNode[set1[i]] = set2[i];
		nodeToString[set2[i]] = set1[i];
	}
		
}

void buildAll()
{
	buildStoN();
	buildMaps();
	buildMatrix();
	buildisOper();
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


bool isOperator[100];
bool doubleOperator[100];

inline void buildisOper()
{
	memset(isOperator, 0, sizeof(isOperator));
	NodeType operlist[] = { PRINTT,
		EQUAL, ADD, MINUS, MULTIPLY, DIVIDE, IS_EQUAL, IS_NOT_EQUAL,
		LEFT_MOVE, RIGHT_MOVE, WHILE, FOR, LISTFLAG, NOT,
		ELIF, ELSE, CONTINUE, BREAK, PASS, RETURN ,BIGGER, SMALLER, BIGGER_OR_EQUAL, SMALLER_OR_EQUAL, AND, OR, WEI_AND, WEI_OR, WEI_YIHUO,
		MOD, ZHENG_DIVIDE };

	NodeType doubleList[] = {
		EQUAL, ADD, MINUS, MULTIPLY, DIVIDE, IS_EQUAL, IS_NOT_EQUAL, 
		LEFT_MOVE, RIGHT_MOVE, LISTFLAG, BIGGER, SMALLER, BIGGER_OR_EQUAL, SMALLER_OR_EQUAL,
		WEI_AND, WEI_OR, WEI_YIHUO, MOD, ZHENG_DIVIDE, AND, OR
	};

	for (auto& it : operlist)
	{
		//cout << nodeToString[operlist[it]] << endl;
		isOperator[it] = true;
	}

	for (auto& it : doubleList)
	{
		doubleOperator[it] = true;
	}
}

