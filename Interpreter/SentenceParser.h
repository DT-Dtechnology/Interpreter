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
	void parserRoot() const { FuncSwitcher(cur_block_,root_); }
	void prepareNode(Node*);
	void prepareRoot() { prepareNode(root_); }
public:
	SentenceParser(Sentence* sentence) :sentence_(sentence) { }
	~SentenceParser() { delete root_; };
	void work();
	void print_test_first();
	void print_test_second();
	
	static void build_all();
};

