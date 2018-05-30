#include "stdafx.h"
#include "Sentence.h"

Sentence::Sentence(std::string& order, int tab, int row)
{
	this->order_ = order;
	this->tab_cnt_ = tab;
	this->row_ = row;
}
