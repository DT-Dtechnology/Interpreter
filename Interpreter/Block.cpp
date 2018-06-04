#include "stdafx.h"
#include "Block.h"
#include "SentenceParser.h"

void Block::print_all()
{
	for (auto it = sentence_vector_->begin(); it != sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		sp->print_test_second();
		delete sp;
	}
}
