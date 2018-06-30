#pragma once
#include "Sentence.h"
#include "Word.h"
#include "Node.h"
#include <queue>

class Block;
class IDLE;
enum ControlStatus;

typedef std::queue<Word> WordQueue;

class SentenceParser
{
	Sentence* sentence_;
	Block* cur_block_;
	WordQueue word_queue_;
	Node* root_ = nullptr;

	void divide();
	void buildTree();
	void parserRoot(){ root_ = FuncSwitcher(cur_block_,root_); }
	void prepareNode(Node*);
	void prepareRoot() { prepareNode(root_); }
	ControlStatus getStatus() const;
public:
	SentenceParser(Sentence* sentence) :sentence_(sentence) { }
	~SentenceParser()
	{
		delete root_;
	};
	ControlStatus work();
	void upFloat();
	void setBlock(Block* cur) { cur_block_ = cur; }
	
	static void build_all();

	friend Traveller;
	friend IDLE;
};

