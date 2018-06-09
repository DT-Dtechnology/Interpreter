#include "stdafx.h"
#include "Block.h"
#include "SentenceParser.h"
#include "PVM.h"

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
			cout << "Find " << var_name << endl;
			system("pause");

			returnSpace();
			return object;
		}
		temp_space_stack_.push(block_space_stack_.top());
		block_space_stack_.pop();
	}
	cout << "Not Find " << var_name << endl;
	system("pause");

	returnSpace();
	return nullptr;
}

Object* Block::changeNode(const string& var_name, Object* object)
{
	var_table_[var_name] = object;
	return object;
}

void Block::print_all() const
{
	for (auto it = sentence_vector_->begin(); it != sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		// #### 
		// ���ﲻ�Ƿǳ���ȫ
		// ���ڻῼ�Ǹ�Ϊ�����еĴ���Block*�Ĳ���ȫ��ת��Ϊconst Block*
		//sp->setBlock();
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
