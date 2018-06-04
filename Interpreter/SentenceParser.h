#pragma once
#include "Sentence.h"
#include "Word.h"
#include <queue>
#include "Node.h"

class Block;

typedef std::queue<Word> WordQueue;

class SentenceParser
{
	Sentence* sentence_;
	Block* cur_block_;
	WordQueue word_queue_;
	Node* root_ = nullptr;

	void divide();
	void buildTree();
	void parserNode(Node*);
	void parserRoot() { parserNode(root_); }
public:
	SentenceParser(Sentence* sentence) :sentence_(sentence) { }
	~SentenceParser() = default;
	void work();
	void print_test_first();
};

