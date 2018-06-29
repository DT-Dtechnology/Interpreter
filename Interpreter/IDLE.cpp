#include "stdafx.h"
#include "IDLE.h"

using std::cin;
using std::cout;
using std::endl;

void IDLE::input()
{
	string tmp;
	int tab_cnt = 0;
	cout << ">>>";
	print_tab();
	std::getline(cin, tmp);
	while (tmp[tab_cnt] == '\t')
	{
		++tab_cnt;
	}
	string order = tmp.substr(tab_cnt, tmp.length() - tab_cnt);
	if(order == "")
		return;
	Sentence* sentence = new Sentence(order, cur_tab, 0);
	parse_sen(sentence);
	cur_tab = 0;

	delete sentence;
}

bool IDLE::getNext(Block* block)
{
	string tmp;
	int tab_cnt = 0;
	print_tab();
	std::getline(cin, tmp);
	while(tmp[tab_cnt] == '\t')
	{
		++tab_cnt;
	}
	string order = tmp.substr(tab_cnt, tmp.length()-tab_cnt);
	if (order == "")
		return true;
	Sentence* sentence = new Sentence(order, cur_tab+tab_cnt, 0);
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
					break;
				}
			}
		}
		// cout << "EndDefFunc" << endl;
		delete sp;
		return;
	}
	if(status == IFTRUE || status == IFFALSE || status == LOOPTRUE || status == LOOPFALSE)
	{
		// ������ʱʹ�õĿ飬�����������ռ䣬ʹ�������ռ���Global_һ��
		Block* tmp_block = new Block();
		tmp_block->sentence_vector_->push_back(sentence);
		

		while (true)
		{
			if (getNext(tmp_block))
			{
				if (getNext(tmp_block))
				{
					break;
				}
			}
		}
		string EndFlag;
		if (status == IFTRUE || status == IFFALSE)
			EndFlag = "endIf";
		else
			EndFlag = "endLoop";
		tmp_block->sentence_vector_->push_back(new Sentence(EndFlag, cur_tab, 0));

		Traveller traveller = Traveller(tmp_block);
		tmp_block->block_space_stack_.pop();
		tmp_block->block_space_stack_.push(Global_);
		traveller.work();
		
	}
}

void IDLE::work()
{
	while(true)
	{
		input();
	}
}

