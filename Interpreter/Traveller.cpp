#include "stdafx.h"
#include "Traveller.h"

void Traveller::work()
{
	while(current_ != c_block_->sentence_vector_->end())
	{
		if ((*current_)->order_ == "endIf")
			// ���б���ж�
		{
			if (status_.top() == IFTRUE)
				status_.pop();
			++current_;
			continue;
		}
		if ((*current_)->order_.substr(0,4) == "else" || (*current_)->order_.substr(0,4) == "elif")
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
		if ((*current_)->order_ == "break")
		{
			while (status_.top() != LOOPTRUE)
			{
				if (!status_.empty())
					status_.pop();
			}
			jump_posi_.pop();
			status_.pop();
			while ((*current_)->order_ != "endLoop")
				++current_;
			++current_;
			continue;
		}
		if ((*current_)->order_ == "continue")
		{
			while (status_.top() != LOOPTRUE)
			{
				if (!status_.empty())
					status_.pop();
			}
			current_ = jump_posi_.top();
			jump_posi_.pop();
			status_.pop();
			continue;
		}

		SentenceParser* sp = new SentenceParser(*current_);
		sp->setBlock(c_block_);
		const ControlStatus status = sp->work();

		if(status == RETURNSTA)
		{
			c_block_->return_pos_ = sp->root_->getValue();
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
	}
}

void Traveller::passOne(ControlStatus cs)
{
	jump_posi_.push(current_);
	++current_;
	status_.push(cs);
}
