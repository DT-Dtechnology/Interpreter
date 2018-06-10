#include "stdafx.h"
#include "Traveller.h"

void Traveller::work()
{
	while(current_ != c_block_->sentence_vector_->end())
	{
		if ((*current_)->order_ == "endIf")
			// 还有别的判断
		{
			if (status_.top() == IFSTA)
				status_.pop();
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
					while ((*current_)->tab_cnt_ > cur_tabs)
						++current_;
				}
		}
		else
		{
			while ((*current_)->order_ != "endIf")
				++current_;
		}
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
		sp->print_test_second();
		delete sp;
	}
}
