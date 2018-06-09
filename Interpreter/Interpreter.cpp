// Interpreter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	SentenceParser::build_all();
	cout << endl;
	const string file_name = "Test1.txt";
	PVM pvm(file_name);
	pvm.print_test_first();
	return 0;
}
