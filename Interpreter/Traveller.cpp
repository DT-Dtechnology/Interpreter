#include "stdafx.h"
#include "Traveller.h"

void Traveller::work() const
{
	for (auto it = c_block_->sentence_vector_->begin();
		it != c_block_->sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		sp->setBlock(c_block_);
		sp->print_test_first();
		delete sp;
	}
}
