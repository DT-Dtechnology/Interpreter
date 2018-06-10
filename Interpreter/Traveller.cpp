#include "stdafx.h"
#include "Traveller.h"

void Traveller::work()
{
	while(current_ != c_block_->sentence_vector_->end())
	{
		if ((*current_)->order_ == "endIf")
			// ���б���ж�
		{
			if (status_.top() == IFSTA)
				status_.pop();
			if(current_ == c_block_->sentence_vector_->end())
				return;
			++current_;
			continue;
		}
		if((*current_)->order_ == "endDef")
		{
			if (status_.top() == DEFSTA)
				status_.pop();
			if (current_ == c_block_->sentence_vector_->end())
				return;
			++current_;
			continue;
		}
		if ((*current_)->order_ == "endLoop")
		{
			cout << "LoopEnd" << endl;
			system("pause");
			if(status_.top() == LOOPTRUE)
			{
				current_ = jump_posi_.top();
				jump_posi_.pop();
				status_.pop();
				continue;
			}
			if (status_.top() == LOOPFALSE)
			{
				status_.pop();
				jump_posi_.pop();
			}
			if (current_ == c_block_->sentence_vector_->end())
				return;
			++current_;
			continue;
		}
		SentenceParser* sp = new SentenceParser(*current_);
		sp->setBlock(c_block_);
		const ControlStatus status = sp->work();
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
			cout << "Normal" << endl;
			system("pause");
			if(next_tabs == cur_tabs)
				++current_;
			else
				if(status == IFTRUE)
				{
					++current_;
					status_.push(IFSTA);
				}
				else if(status == IFFALSE)
				{
					// cout << "GG" << endl;
					++current_;
					while ((*current_)->tab_cnt_ != cur_tabs)
						++current_;
				}
				else if(status == DEFSTA)
				{
					status_.push(DEFSTA);
					// Let Us Create a Block
				}
				else if(status == LOOPTRUE)
				{
					jump_posi_.push(current_);
					status_.push(LOOPTRUE);
					++current_;
				}
				else if(status == LOOPFALSE)
				{
					status_.push(LOOPFALSE);
					++current_;
					while ((*current_)->tab_cnt_ != cur_tabs)
						++current_;
				}
		}
		else
		{
			if (status_.top() == IFSTA)
			{
				system("pause");
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
		
		cout << "Next" << endl;
		system("pause");

		delete sp;
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
