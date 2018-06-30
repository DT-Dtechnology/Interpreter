#pragma once
#include "Block.h"
#include "Inputter.h"
#include "Traveller.h"

/**
 * \brief 
 * PVMΪ����Python�ļ����е��������������Ŀ����Ϊ�����������ԵĿ��ơ�
 * ʵ�ֵĹ���Ϊ�����ļ�������ִ�С�ִ�й���������������ݻ�������еĽ����
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

