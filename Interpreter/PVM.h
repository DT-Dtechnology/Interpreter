#pragma once
#include "Block.h"
#include "Inputter.h"
#include "Traveller.h"

/**
 * \brief 
 * PVM为整体Python文件运行的虚拟机。建立的目的是为了做到整体性的控制。
 * 实现的功能为读入文件，单句执行。执行过程中依据语句内容会输出运行的结果。
 */
class PVM
{
	string file_name_;
	Block* Global_;
	Traveller* Global_Traveler_;

	void input();
	void run() const;
public:
	PVM(string file_name) :file_name_(file_name)
	{
		input();
	}
	~PVM() = default;
	void work() const
	{
		run();
	}
	void print_test_first();
	void print_test_second();
	friend Block;
};

inline void PVM::input()
{
	ifstream fin;
	fin.open(file_name_);
	Inputter* inputter = new Inputter(fin);
	Global_ = new Block(inputter->get_sentence_vector());
	Global_Traveler_ = new Traveller(Global_);
	delete inputter;
}

inline void PVM::run() const
{
	Global_Traveler_->work();
}

inline void PVM::print_test_first()
{
	input();
	std::cout << "Hello World" << std::endl << std::endl;
	Global_->print_all();
}

inline void PVM::print_test_second()
{
	input();
	std::cout << "Hello World" << std::endl << std::endl;
	Global_->print_all_old();
}

