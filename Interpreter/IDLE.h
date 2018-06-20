#pragma once
#include "Block.h"

class IDLE
{
	Block* Global_;

	bool repeat_ = false;
	int cur_tab = 0;

	void input();
	bool getNext(Block* block);
	void print_tab() const;
	void parse_sen(Sentence* sentence);
public:
	void work();

	IDLE()
	{
		Global_ = new Block();
		Global_->block_space_stack_.push(Global_);
	};
	~IDLE()
	{
		delete Global_;
	};
};

