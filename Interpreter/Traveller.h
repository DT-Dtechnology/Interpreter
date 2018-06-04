#pragma once
#include "SentenceParser.h"

class Traveller
{
	Block* c_block_;
public:
	Traveller(Block* c_block) :c_block_(c_block) { ; }
	~Traveller() = default;
	void work();
};

