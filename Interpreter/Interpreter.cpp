// Interpreter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	/*
	SentenceParser::build_all();
	cout << endl;
	const string file_name = "Test1.txt";
	PVM pvm(file_name);
	pvm.print_test_first();
	*/

	Object * T1 = new StringObject("ab");
	Object * T2 = new StringObject("ef");

	Object *res = T1->equal(T2);
	BoolObject *res2 = dynamic_cast<BoolObject *>(res);
	cout << res2->get_val() << endl << "-" << endl;

	system("pause");
	return 0;
}
