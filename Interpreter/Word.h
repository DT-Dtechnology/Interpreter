#pragma once
#include <string>
#include "Object.h"

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
	Word() = default;
	~Word() = default;
	Word(WordType type, string str) :word_type_(type), msg_(str) { }
	string getMsg() const { return msg_; }
	void setMsg(string msg) { msg_ = msg; }
	WordType getType() const { return word_type_; }
};
