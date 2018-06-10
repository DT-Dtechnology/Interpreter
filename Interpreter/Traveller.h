#pragma once
#include "Block.h"

enum ControlStatus
{
	IFSTA, LOOPSTA, DEFSTA, NORMALSTA, USELESS,
	IFTRUE, IFFALSE, LOOPTRUE, LOOPFALSE
};

typedef stack<ControlStatus> StatusControl;

class Traveller
{
	Block* c_block_;
	SenVector::iterator current_;
	StatusControl status_;
public:
	Traveller(Block* c_block) :c_block_(c_block)
	{
		c_block->block_space_stack_.push(c_block);
		status_.push(NORMALSTA);
		current_ = c_block_->sentence_vector_->begin();
	}
	~Traveller() = default;
	void work();
	void work_test() const;
};

