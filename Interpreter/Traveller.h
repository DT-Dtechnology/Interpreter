#pragma once
#include "SentenceParser.h"

class Traveller
{
	Block* c_block_;
	SentenceParser sentence_parser_;
public:
	Traveller() = default;
	~Traveller() = default;
	void work();
};

