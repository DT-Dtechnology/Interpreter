#include "stdafx.h"
#include "Traveller.h"

void Traveller::work()
{
	while(current_ != c_block_->sentence_vector_->end())
	{
		if ((*current_)->order_ == "endIf")
			// 还有别的判断
		{
			if (status_.top() == IFTRUE)
				status_.pop();
			
			++current_;
			continue;
		}
		if ((*current_)->order_ == "else" || (*current_)->order_ == "elif")
		{
			if (status_.top() == IFTRUE)
			{
				++current_;
				while ((*current_)->getOrder() != "endIf") {
					++current_;
				}
				continue;
			}
		}
		if((*current_)->order_ == "endDef")
		{
			if (status_.top() == DEFSTA)
				status_.pop();
			
			++current_;
			continue;
		}
		if ((*current_)->order_ == "endLoop")
		{
			if(status_.top() == LOOPTRUE)
			{
				current_ = jump_posi_.top();
				jump_posi_.pop();
				status_.pop();
			}
			else if (status_.top() == LOOPFALSE)
			{
				status_.pop();
				++current_;
			}else
			{
				++current_;
			}
			
			continue;
		}
		SentenceParser* sp = new SentenceParser(*current_);
		sp->setBlock(c_block_);
		const ControlStatus status = sp->work();
		if(status == RETURNSTA)
		{
			c_block_->return_pos_ = sp->root_->getValue();
			if (c_block_->return_pos_)
			{
				c_block_->return_pos_->print_test();
				system("pause");
			}
			return;
		}
		const int cur_tabs = (*current_)->tab_cnt_;
		++current_;
		if(current_ == c_block_->sentence_vector_->end())
		{
			delete sp;
			return;
		}
		const int next_tabs = (*current_)->tab_cnt_;
		--current_;
		if (next_tabs >= cur_tabs)
		{
			if(next_tabs == cur_tabs)
				++current_;
			else
			{
				if (status == IFTRUE)
				{
					++current_;
					status_.push(IFTRUE);
				}
				else if (status == IFFALSE)
				{
					// cout << "GG" << endl;
					++current_;
					while ((*current_)->tab_cnt_ != cur_tabs)
						++current_;
				}
				else if (status == LOOPTRUE)
				{
					jump_posi_.push(current_);
					status_.push(LOOPTRUE);
					++current_;
				}
				else if (status == LOOPFALSE)
				{
					status_.push(LOOPFALSE);
					++current_;
					while ((*current_)->tab_cnt_ != cur_tabs)
						++current_;
				}
				else if (status == DEFSTA)
				{
					const string func_name = sp->root_->getValue()->getName();
					Block* block = c_block_->func_table_[func_name];
					++current_;
					while ((*current_)->getOrder() != "endDef")
					{
						block->sentence_vector_->push_back(*current_);
						++current_;
					}

					cout << "Def a Function" << endl;
					for(auto it = block->sentence_vector_->begin() ; it != block->sentence_vector_->end();
						++it)
					{
						cout << (*it)->getOrder() << endl;
					}
					cout << "Size:" << block->sentence_vector_->size() << endl;
					system("pause");
					cout << endl;
				}
			}
		}
		else
		{
			if (status_.top() == IFTRUE
				)
			{
				while ((*current_)->order_ != "endIf")
					++current_;
			}
			else if(status_.top() == LOOPTRUE)
			{
				current_ = jump_posi_.top();
				jump_posi_.pop();
				status_.pop();
			}
		}
		delete sp;
		system("pause");
	}
}

void Traveller::work_test() const
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
