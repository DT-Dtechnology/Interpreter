#pragma once
#include "Block.h"
#include "Inputter.h"

class PVM
{
	Block* Global_;
	string file_name_;

	void input();
	void run();
public:
	PVM(string file_name) :file_name_(file_name) { }
	~PVM();
	void work()
	{
		input();
		run();
	}
};

inline void PVM::input()
{
	Inputter* inputter = new Inputter(file_name_);
	Global_ = new Block(inputter->get_sentence_vector());
	delete inputter;
}

inline void PVM::run()
{
	
}

