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

Block* Block::addBlock(const string& name, const vector<string>& name_list)
{
	Block* block = new Block();
	for(auto it = name_list.begin() ; it != name_list.end() ; ++it)
		block->para_name_.push_back(*it);
	func_table_[name] = block;
	return block;
}

Block* Block::searchObjectBlock(const string& var_name)
{
	//####
	//####
	//return nullptr;
	//####
	//####
	Block* block = nullptr;
	Object* return_object = nullptr;
	while(!block_space_stack_.empty())
	{
		return_object = block_space_stack_.top()->var_table_[var_name];
		if (return_object != nullptr)
		{
			// cout << "Find " << var_name << endl;
			// system("pause");

			block = block_space_stack_.top();
			returnSpace();
			return block;
		}
		temp_space_stack_.push(block_space_stack_.top());
		block_space_stack_.pop();
	}
	// cout << "Not Find " << var_name << endl;
	// system("pause");
	returnSpace();
	block = block_space_stack_.top();
	return block;
}

Object* Block::searchObject(const string& var_name)
{
	Object* return_object = nullptr;
	while (!block_space_stack_.empty())
	{
		return_object = block_space_stack_.top()->var_table_[var_name];
		if (return_object != nullptr)
		{
			// cout << "Find " << var_name << endl;
			// system("pause");

			returnSpace();
			return return_object;
		}
		temp_space_stack_.push(block_space_stack_.top());
		block_space_stack_.pop();
	}
	// cout << "Not Find " << var_name << endl;
	// system("pause");
	returnSpace();
	return return_object;
}

Object* Block::changeVar(const string& var_name, Object* object)
{
	if (object->getType() == ListObj)
	{
		ListObject* obj = dynamic_cast<ListObject*>(object);
		ListObject* new_obj = new ListObject(*obj);
		var_table_[var_name] = new_obj;
	}
	else if (object->getType() == LongObj)
	{
		LongObject* obj = dynamic_cast<LongObject*>(object);
		LongObject* new_obj = new LongObject(*obj);
		var_table_[var_name] = new_obj;
	}
	else if (object->getType() == DoubleObj)
	{
		DoubleObject* obj = dynamic_cast<DoubleObject*>(object);
		DoubleObject* new_obj = new DoubleObject(*obj);
		var_table_[var_name] = new_obj;
	}
	else if(object->getType() == BoolObj)
	{
		BoolObject* obj = dynamic_cast<BoolObject*>(object);
		BoolObject* new_obj = new BoolObject(*obj);
		var_table_[var_name] = new_obj;
	}
	else if(object->getType() == StringObj)
	{
		StringObject* obj = dynamic_cast<StringObject*>(object);
		StringObject* new_obj = new StringObject(*obj);
		var_table_[var_name] = new_obj;
	}
	else
	{
		throw Error("Unknown Type");
	}
	
	return object;
}

void Block::print_all() const
{
	for (auto it = sentence_vector_->begin(); it != sentence_vector_->end(); ++it)
	{
		SentenceParser* sp = new SentenceParser((*it));
		// #### 
		// 这里不是非常安全
		// 后期会考虑改为将所有的传入Block*的参数全部转化为const Block*
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
