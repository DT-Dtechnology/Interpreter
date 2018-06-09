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

	Object *T1 = new StringObject ("\"abc%d--%d------%d-\"");
	Object *T2 = new LongObject (test2);
	Object *T3 = new LongObject(test4);
	Object *T4 = new LongObject(test1);

	vector<Object *> temp;
	temp.push_back(T4);
	temp.push_back(T2);
	temp.push_back(T3);
	Object *T5 = new ListObject(temp);

	Object *res = T1->mod(T5);
	StringObject *res2 = dynamic_cast<StringObject *>(res);
	cout << res2->get_val();


	system("pause");
	return 0;
}
