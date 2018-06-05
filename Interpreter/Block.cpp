#include "stdafx.h"
#include "Block.h"
#include "SentenceParser.h"

void Block::returnSpace()
{
	while(!temp_space_stack_.empty())
	{
		block_space_stack_.push(temp_space_stack_.top());
		temp_space_stack_.pop();
	}
}

Object* Block::searchObject(string var_name)
{
	//####
	//####
	return nullptr;
	//####
	//####
	Object* object = nullptr;
	while(!block_space_stack_.empty())
	{
		object = block_space_stack_.top()->var_table_[var_name];
		if (object != nullptr)
		{
			returnSpace();
			return object;
		}
		temp_space_stack_.push(block_space_stack_.top());
		block_space_stack_.pop();
	}
	returnSpace();
	return nullptr;
}

void Block::print_all()
{
	for (auto it = sentence_vector_->begin(); it != sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		sp->print_test_second();
		delete sp;
	}
}
