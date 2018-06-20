#include "stdafx.h"
#include "IDLE.h"

using std::cin;
using std::cout;
using std::endl;

void IDLE::input()
{
	string order;
	cout << ">>>";
	print_tab();
	std::getline(cin, order);
	Sentence* sentence = new Sentence(order, cur_tab, 0);
	parse_sen(sentence);
	cur_tab = 0;

	delete sentence;
}

bool IDLE::getNext(Block* block)
{
	string order;
	print_tab();
	std::getline(cin, order);
	if (order == "")
		return true;
	Sentence* sentence = new Sentence(order, cur_tab, 0);
	block->sentence_vector_->push_back(sentence);
	return false;
}


void IDLE::print_tab() const
{
	for(auto it = 0 ; it < cur_tab ; ++it)
		cout << "\t";
}

void IDLE::parse_sen(Sentence* sentence)
{
	SentenceParser* sp = new SentenceParser(sentence);
	sp->setBlock(Global_);
	const ControlStatus status = sp->work();
	if(status == DEFSTA)
	{
		const string func_name = sp->root_->getValue()->getName();
		Block* block = Global_->func_table_[func_name];
		++cur_tab;
		while(true)
		{
			if(getNext(block))
			{
				if (getNext(block))
				{
					string end_msg("EndDef");
					block->sentence_vector_->push_back(new Sentence(end_msg, 0, 0));
					break;
				}
			}
		}
		cout << "EndDefFunc" << endl;
		delete sp;
		return;
	}
}

void IDLE::work()
{
	while(true)
	{
		input();
	}
}

