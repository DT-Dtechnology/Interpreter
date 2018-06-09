#pragma once
#include <stack>
#include <map>
#include "Object.h"
#include "Traveller.h"

class Block;

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
	Traveller traveller_;
	Object* return_pos_ = nullptr;

	void returnSpace();
public:
	Block(SenVector* sen_vector) :sentence_vector_(sen_vector), traveller_(this) { }
	~Block() = default;
	
	Object* searchObject(string var_name);

	void print_all() const;
	void print_all_old();
};
