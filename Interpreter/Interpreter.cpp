// Interpreter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int main()
{
	SentenceParser::build_all();
	IDLE idle;
	idle.work();
	return 0;
	
}
