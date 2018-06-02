#pragma once
#include <string>
#include <vector>
#include "Word.h"
#include "Sentence.h"
#include <queue>

using std::string;
using std::vector;
using std::queue;


class SentencePart
{
public:
	WordType type;
	string word;
	SentencePart(WordType t, string s = "") :type(t), word(s) { }
	WordType getType() const { return type; }
	string getWord() const { return word; }
	void display() const
	{
		std::cout << word << std::endl;
	}
};

//typedef SentencePart Word;
typedef queue<SentencePart> WordQueue;

class ParserNode
{
	SentencePart value;
	vector<ParserNode*> child;
	ParserNode* parent;
public:
	ParserNode() = default;
	~ParserNode() = default;
};

class SentenceDivider
{
	string command;
public:
	SentenceDivider(const string& SQL) :command(SQL) {}
	~SentenceDivider() = default;
	WordQueue* work();

	//####
	void display()
	{
		std::cout << command << std::endl;
		WordQueue* temp = work();
		while (!temp->empty())
		{
			temp->front().display();
			temp->pop();
		}
	}
};
