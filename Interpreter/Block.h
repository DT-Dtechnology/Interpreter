#pragma once
#include <stack>
#include <map>
#include "Sentence.h"

class Object;
class Block;
class Traveller;

using std::stack;
using std::map;
using std::string;
using std::vector;

typedef vector<Sentence*> SenVector;
typedef map<string, Object*> VarTable;
typedef map<string, Block*> FuncTable;

class Block
{
	SenVector* sentence_vector_;
	stack<Block*> block_space_stack_;
	stack<Block*> temp_space_stack_;
	VarTable var_table_;
	FuncTable func_table_;
	Object* return_pos_ = nullptr;

	void returnSpace();
public:
	Block(SenVector* sen_vector) :sentence_vector_(sen_vector) { }
	~Block() = default;
	
	Block* searchObjectBlock(const string& var_name);
	Object* searchObject(const string& var_name);
	Object* changeNode(const string& var_name, Object* object);

	void print_all() const;
	void print_all_old() const;

	friend Traveller;
};
