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
 * Block���ڼ�¼�������͸����Զ��庯�������еĻ���,�����а����������ռ������˳�򣬵�ǰ�����д洢���Ѷ���ĺ����ͱ�����
 * �ر�ע�⵽Python����ʹ���˾�̬�����ռ�,���Ի��ڳ�ʼ������������ͬʱ����Ĵ���Traveler�ڹ�����Ϊ����������ռ䡣
 * ͬʱ�洢�˷��ض�������ʵ�ֺ�����return����
 * 
 * ������������Ӻ����������ĺ���,��Ӻ����������ĺ���,��������������ʵ���˲㼶����
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
		std::cout << "deleteing block: " << std::endl;
		getchar();
		if (return_pos_)
			delete return_pos_;
		if (sentence_vector_) {
			while (!sentence_vector_->empty()) {
				auto i = sentence_vector_->front();
				delete i;
			}
			delete sentence_vector_;
		}
		while (!block_space_stack_.empty()) {
			auto i = block_space_stack_.top();
			delete i;
		}
		while (!temp_space_stack_.empty()) {
			auto i = block_space_stack_.top();
			delete i;
		}
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
