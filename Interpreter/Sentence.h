#pragma once
#include <string>
#include <iostream> // 

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
	~Sentence();
	string getOrder() const { return order_; }
	void printTest() const { std::cout << row_ << " " << tab_cnt_ << " " << order_ << '\n'; }
	
	friend Traveller;
};

inline Sentence::Sentence(std::string& order, int tab, int row):
	order_(order),tab_cnt_(tab),row_(row)
{
	
}
