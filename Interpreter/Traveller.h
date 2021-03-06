#pragma once
#include "Block.h"

enum ControlStatus
{
	IFSTA, LOOPSTA, DEFSTA, NORMALSTA, USELESS,
	IFTRUE, IFFALSE, LOOPTRUE, LOOPFALSE, RETURNSTA
};

typedef stack<ControlStatus> StatusControl;
typedef stack<SenVector::iterator> JumpPosiStack;

class Traveller
{
	Block* c_block_;
	SenVector::iterator current_{};
	StatusControl status_{};
	JumpPosiStack jump_posi_{};
public:
	Traveller(Block* c_block) :c_block_(c_block)
	{
		c_block->block_space_stack_.push(c_block);
		status_.push(NORMALSTA);
		current_ = c_block_->sentence_vector_->begin();
	}
	Traveller(Block* parent, Block* c_block):c_block_(c_block)
	{
		c_block->temp_space_stack_.push(c_block);
		while(!parent->block_space_stack_.empty())
		{
			parent->temp_space_stack_.push(parent->block_space_stack_.top());
			c_block->temp_space_stack_.push(parent->block_space_stack_.top());
			parent->block_space_stack_.pop();
		}
		parent->returnSpace();
		c_block->returnSpace();
		status_.push(NORMALSTA);
		current_ = c_block_->sentence_vector_->begin();
	}
	~Traveller()
	{
		c_block_->block_space_stack_.pop();
		auto it = c_block_->var_table_.begin();
		while (it != c_block_->var_table_.end())
		{
			it = c_block_->var_table_.erase(it);
		}
	};
	// For PVM
	void work();

	// For IDLE
	void passOne(ControlStatus);
};

