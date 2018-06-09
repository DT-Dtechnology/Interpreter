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

Object* Block::searchObject(const string& var_name)
{
	//####
	//####
	//return nullptr;
	//####
	//####
	Object* object = nullptr;
	while(!block_space_stack_.empty())
	{
		object = block_space_stack_.top()->var_table_[var_name];
		if (object != nullptr)
		{
			cout << "Find" << endl;
			system("pause");

			returnSpace();
			return object;
		}
		temp_space_stack_.push(block_space_stack_.top());
		block_space_stack_.pop();
	}
	cout << "Not Find" << endl;
	system("pause");

	returnSpace();
	return addObjetc(var_name);
}

Object* Block::addObjetc(const string& var_name)
{
	Object* obj= new Object(ObjectType::TotalValue);
	var_table_[var_name] = obj;
	return obj;
}

void Block::print_all() const
{
	for (auto it = sentence_vector_->begin(); it != sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		// #### 
		// 这里不是非常安全
		// 后期会考虑改为将所有的传入Block*的参数全部转化为const Block*
		sp->setBlock(this);
		sp->print_test_second();
		delete sp;
	}
}

void Block::print_all_old() const
{
	for (auto it = sentence_vector_->begin(); it != sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		sp->print_test_first();
		delete sp;
	}
}
