#pragma once

enum SentenceType
{
	SentenceLoop, SentenceIf, SentenceDef, SentenceReturn, SentenceExp
};

class Sentence
{
	SentenceType senType_;
	int tab_cnt_;
	//int row;
public:
	Sentence() {}
	~Sentence() {}
};
