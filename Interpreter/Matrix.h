#pragma once
#include "Node.h"
#include <string>
#include <map>
#include <fstream>

using std::string;
using std::map;

const int MatrixRow = 23;
const int MatrixColumn = 31;

//####
bool isUnTerminate[256];
void buildIsUnTerminate()
{
	for (int i = 0; i < 256; i++)
		isUnTerminate[i] = false;
	char UTsets[] = { 'E', 'E' - 64, 'T', 'T' - 64, 'F', 'F' - 64, 'G', 'G' - 64, 'H', 'S' - 64, 'A', 'L', 'W', 'W' - 64, 'D', 'Q', 'S', 'P', 'V' - 64, 'R', 'I', 'J', 'P' - 64 };
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
	char Tsets[] = { 'i', 'a', 'b', '#', 'c', 'd', '+' , '-', '*', '/', '(', ')', '=', 'l', ':', 'n', 'o', ',', 'q', '!', 'r', 's', 't', 'u', 'v', 'w', 'e', 'x', 'y', 'z', 'f' };
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
	char UTsetc[] = { 'E', 'E' - 64, 'T', 'T' - 64, 'F', 'F' - 64, 'G', 'G' - 64, 'H', 'S' - 64, 'A', 'L', 'W', 'W' - 64, 'D', 'Q', 'S', 'P', 'V' - 64, 'R', 'I', 'J', 'P' - 64 };
	string UTsets[MatrixRow];
	for (int i = 0; i < MatrixRow; ++i ) {
		UTsets[i] = UTsetc[i];
	}
	for (int i = 0; i < MatrixRow; i++) {
		stringToChar[UTsets[i]] = UTsetc[i];
	}
	char Tsetc[] = { 'i', 'a', 'b', '#', 'c', 'd', '+' , '-', '*', '/', '(', ')', '=', 'l', ':', 'n', 'o', ',', 'q', '!', 'r', 's', 't', 'u', 'v', 'w', 'e', 'x', 'y', 'z', 'f' };
	string Tsets[MatrixColumn];
	for (int i = 0; i < MatrixColumn; ++i) {
		Tsets[i] = Tsetc[i];
	}
	for (int i = 0; i < MatrixColumn; i++) {
		stringToChar[Tsets[i]] = Tsetc[i];
	}
}

// Nodetype enum
// 行数
map<NodeType, int> nodeToInt;
void buildNtoI()
{
	nodeToInt[EXP] = 0;
	nodeToInt[EE] = 1;
	nodeToInt[T] = 2;
	nodeToInt[TT] = 3;
	nodeToInt[F] = 4;
	nodeToInt[FF] = 5;
	nodeToInt[G] = 6;
	nodeToInt[GG] = 7;
	nodeToInt[H] = 8;
	nodeToInt[SEN] = 9;
	nodeToInt[ASS] = 10;
	nodeToInt[LOOP] = 11;
	nodeToInt[EXPL] = 12;
	nodeToInt[EXPLL] = 13;
	nodeToInt[DEF] = 14;
	nodeToInt[FUNC] = 15;
	nodeToInt[SUF] = 16;
	nodeToInt[PRO] = 17;
	nodeToInt[VARL] = 18;
	nodeToInt[VARLL] = 19;
	nodeToInt[IF] = 20;
	nodeToInt[JUMP] = 21;
	nodeToInt[PRINT] = 22;
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
	charToNode['E'] = EXP;
	charToNode['E' - 64] = EE;
	charToNode['T'] = T;
	charToNode['T' - 64] = TT;
	charToNode['F'] = F;
	charToNode['F' - 64] = FF;
	charToNode['G'] = G;
	charToNode['G' - 64] = GG;
	charToNode['H'] = H;
	charToNode['Q'] = FUNC;
	charToNode['S' - 64] = SEN;
	charToNode['L'] = LOOP;
	charToNode['I'] = IF;
	charToNode['J'] = JUMP;
	charToNode['D'] = DEF;
	charToNode['P' - 64] = PRINT;
	charToNode['A'] = ASS;
	charToNode['W'] = EXPL;
	charToNode['W' - 64] = EXPLL;
	charToNode['S'] = SUF;
	charToNode['P'] = PRO;
	charToNode['V'-64] = VARL;
	charToNode['R'] = VARLL;
	//'=', '#', '(', ')', 'b', 'c', '+', '-', '*', '/'
	charToNode['='] = EQUAL;
	charToNode['('] = LEFT_BRACKET;
	charToNode[')'] = RIGHT_BRACKET;
	charToNode['+'] = ADD;
	charToNode['-'] = MINUS;
	charToNode['*'] = MULTIPLY;
	charToNode['/'] = DIVIDE;
	charToNode['a'] = IS_EQUAL;
	charToNode['b'] = IS_NOT_EQUAL;
	charToNode['c'] = LEFT_MOVE;
	charToNode['d'] = RIGHT_MOVE;
	charToNode['l'] = WHILE;
	charToNode['n'] = FOR;
	charToNode['o'] = IN;
	charToNode[','] = COMMA;
	charToNode[':'] = COLON;
	charToNode['q'] = DEF;
	charToNode['!'] = BANG;
	charToNode['r'] = NOT;
	charToNode['s'] = PLUS_PLUS;
	charToNode['t'] = MINUS_MINUS;
	charToNode['u'] = IF;
	charToNode['v'] = ELIF;
	charToNode['w'] = ELSE;
	charToNode['x'] = CONTINUE;
	charToNode['y'] = BREAK;
	charToNode['z'] = PASS;
	charToNode['e'] = RETURN;
	charToNode['f'] = PRINT;
	charToNode['i'] = VARIABLE;
	charToNode['#'] = END;
}
void buildMatrix();

// 列号
map<string, int> stringToInt;
void buildStoI()
{
	stringToInt["variable"] = 0;
	stringToInt["=="] = 1;
	stringToInt["!="] = 2;
	stringToInt["#"] = 3;
	stringToInt["<<"] = 4;
	stringToInt[">>"] = 5;
	stringToInt["+"] = 6;
	stringToInt["-"] = 7;
	stringToInt["*"] = 8;
	stringToInt["/"] = 9;
	stringToInt["("] = 10;
	stringToInt[")"] = 11;
	stringToInt["="] = 12;
	stringToInt["while"] = 13;
	stringToInt[":"] = 14;
	stringToInt["for"] = 15;
	stringToInt["in"] = 16;
	stringToInt[","] = 17;
	stringToInt["def"] = 18;
	stringToInt["!"] = 19;
	stringToInt["not"] = 20;
	stringToInt["++"] = 21;
	stringToInt["--"] = 22;
	stringToInt["if"] = 23;
	stringToInt["elif"] = 24;
	stringToInt["else"] = 25;
	stringToInt["return"] = 26;
	stringToInt["continue"] = 27;
	stringToInt["break"] = 28;
	stringToInt["pass"] = 29;
	stringToInt["print"] = 30;
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
		if (c == 39)
		{
			str[str.length() - 1] -= 64;
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