#pragma once
#include "Sentence.h"
#include "Word.h"
#include "Node.h"
#include <queue>

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
	void upFloat();
	void setBlock(Block* cur) { cur_block_ = cur; }
	void print_test_first();
	void print_test_second();
	
	static void build_all();
};

