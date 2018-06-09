#pragma once
#include "Block.h"

class Traveller
{
	Block* c_block_;
public:
	Traveller(Block* c_block) :c_block_(c_block)
	{
		c_block->block_space_stack_.push(c_block);
	}
	~Traveller() = default;
	void work() const;
};

