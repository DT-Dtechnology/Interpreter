#pragma once
#include "Sentence.h"
#include "Word.h"
#include <vector>
#include "Node.h"

class Block;

typedef std::vector<Word> WordVector;

class SentenceParser
{
	Sentence* sentence_;
	Block* cur_block_;
	WordVector word_vector_;
	Node* root_;

	void divide();
	void buildTree();
	void parserNode(Node*);
	void parserRoot() { parserNode(root_); }
public:
	SentenceParser() {}
	~SentenceParser() {}
	void work();
};

