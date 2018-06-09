// Interpreter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	/*
	SentenceParser::build_all();
	cout << endl;
	system("pause");
	const string file_name = "Test1.txt";
	PVM pvm(file_name);
	pvm.print_test_first();
	*/

	long test1 = 10;
	long test2 = 3;
	long test4 = 5;
	double test3 = 3.0;

	bool test5 = true;
	bool test6 = false;

	Object *T1 = new BoolObject (test5);
	Object *T2 = new BoolObject (test6);

	Object *res = T1->ByteAnd(T2);
	BoolObject *res2 = dynamic_cast<BoolObject*>(res);

	cout << res2->get_val() << endl << "-" << endl;
	
	res = T1->Or(T2);
	res2 = dynamic_cast<BoolObject*>(res);
	cout << res2->get_val() << endl << "--" << endl;

	res = T1->Not();
	res2 = dynamic_cast<BoolObject*>(res);
	cout << res2->get_val() << endl << "---" << endl;

	system("pause");
	return 0;
}
