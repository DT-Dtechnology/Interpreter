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
	~PVM() = default;
	void work()
	{
		input();
		run();
	}
	void print_test_first();
};

inline void PVM::input()
{
	ifstream fin;
	fin.open(file_name_);
	Inputter* inputter = new Inputter(fin);
	Global_ = new Block(inputter->get_sentence_vector());
	delete inputter;
}

inline void PVM::run()
{
	
}

inline void PVM::print_test_first()
{
	input();
	std::cout << "Hello World" << std::endl << std::endl;
	Global_->print_all();
}

