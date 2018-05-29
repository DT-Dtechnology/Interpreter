#pragma once
#include <string>

using std::string;

enum WordType
{
	value, variable, operate,
	keyword, word_type_error
};

class Word
{
	WordType word_type_;
	string msg_;
public:
	Word();
	~Word();
};
