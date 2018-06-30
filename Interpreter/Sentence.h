#pragma once
#include <string>
#include <iostream>

using std::string;
class Traveller;

enum SentenceType
{
	SentenceLoop, SentenceIf, SentenceDef, SentenceReturn, SentenceExp
};

class Sentence
{
	SentenceType senType_;
	string order_;
	int tab_cnt_;
	int row_; //
public:
	Sentence() = delete;
	Sentence(std::string& order, int tab, int row);
	~Sentence() = default;
	string getOrder() const { return order_; }
	int getRow() const { return row_; }
	int getTab() const { return tab_cnt_; }
	void setRow(int r) { row_ = r; }
	
	friend Traveller;
};

inline Sentence::Sentence(std::string& order, int tab, int row):
	order_(order),tab_cnt_(tab),row_(row)
{
	
}
