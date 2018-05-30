#pragma once
#include "Inputter.h"

void InputterTest()
{
	string name = "InputterTest.txt";
	Inputter Test(name);
	Test.transfer();
	SentenceVector sv = Test.get_sentence_vector();
	sv.printTest();
}
