#pragma once
#include <stack>
#include <map>
#include "Sentence.h"

class Object;
class Block;
class Traveller;
class IDLE;

using std::stack;
using std::map;
using std::string;
using std::vector;

typedef vector<Sentence*> SenVector;
typedef map<string, Object*> VarTable;
typedef map<string, Block*> FuncTable;

/**
 * \brief 
 * Block用于记录主函数和各个自定义函数的运行的环境,环境中包含了命名空间的搜索顺序，当前环境中存储的已定义的函数和变量。
 * 特别注意到Python语言使用了静态命名空间,所以会在初始化过程中利用同时构造的代理Traveler在构造中为其添加命名空间。
 * 同时存储了返回对象。用于实现函数的return返回
 * 
 * 类中内置了添加和搜索变量的函数,添加和搜索函数的函数,其中搜索过程中实现了层级搜索
 */
class Block
{
	SenVector* sentence_vector_;
	stack<Block*> block_space_stack_{};
	stack<Block*> temp_space_stack_{};
	VarTable var_table_{};
	FuncTable func_table_{};
	Object* return_pos_ = nullptr;
	vector<string> para_name_{};

	void returnSpace();
public:
	Block(SenVector* sen_vector) :sentence_vector_(sen_vector) { }
	Block() { sentence_vector_ = new SenVector; };
	~Block() {
		delete sentence_vector_;
		delete return_pos_;
		para_name_.clear();		
	}
	
	Block* addFunc(const string& name, const vector<string>& name_list);
	Block* searchFunc(const string& name);

	Block* searchObjectBlock(const string& var_name);
	Object* searchObject(const string& var_name);
	Object* changeVar(const string& var_name, Object* object);

	void setValue(const vector<Object*>&);

	void print_all() const;
	void print_all_old() const;

	Object* return_value() const { return return_pos_; };

	friend Traveller;
	friend IDLE;
};
