#pragma once
#include <iostream>
#include <vector>
#include "Block.h"
#include "ObjectFactory.h"

/*
 * 本文件定义了全部需要的Object类型，利用虚函数调用的方式实现了函数多态
 */

using std::string;
using std::vector;

enum ObjectType
{
	TEMP_OBJ, TotalVariable, TotalValue, Operator, LongObj,
	DoubleObj, StringObj, TupleObj, ListObj, DictObj,
	BoolObj, FuncObj
};

/**
 * \brief 
 * 基类，但并非抽象类。作为非抽象类，作用为存储Python中间过程中尚未解析的初始定义变量。存储变量所出现位置和名字，方便后续解析。作为中间对象使用。
 * 同时记录了自身的属性type，用于在C++中访问具体数据时进行受控制的动态转化。
 */
class Object
{
	ObjectType type_;
	bool isTemp_ = true;
	string name_;
	Block* cur_ = nullptr;
public:
	Object(ObjectType type) :type_(type) { }
	virtual ~Object() = default;

	ObjectType getType() const { return type_; }
	void setUnTemp() { isTemp_ = false; }
	bool getStatus() const { return isTemp_; }
	virtual void print() const {}

	double get_val();
	void getPosition(const string& name)
	{
		name_ = name;
		cur_ = cur_->searchObjectBlock(name);
	}
	void setBlock(Block* block) { cur_ = block; }
	void setName(const string& name) { name_ = name; }
	string getName() const {return name_;}
	Block* get_block() const { return cur_; }

	virtual Object * add(Object *obj);
	virtual Object * minus(Object *obj);
	virtual Object * multiply(Object *obj);
	virtual Object * divide(Object *obj);

	virtual Object * more_or_equal(Object *obj);
	virtual Object * more(Object *obj);
	virtual Object * less_or_equal(Object *obj);
	virtual Object * less(Object *obj);
	
	virtual Object * equal(Object *obj);
	virtual Object * not_equal(Object *obj);

	virtual Object * leftmove(Object *obj);
	virtual Object * rightmove(Object *obj);

	virtual Object * mod(Object *obj);

	virtual Object * And(Object *obj);
	virtual Object * Or (Object *obj);
	virtual Object * Not();

	virtual Object * ByteAnd(Object * obj);
	virtual Object * ByteOr(Object * obj);
	virtual Object * Xor(Object * obj);

	virtual Object * negative();
	
	int list_posi = -1;

	friend Block;
	friend ObjectFactory;
};

class ValueObject :
	public Object
{
public:
	ValueObject() :Object(ObjectType::TotalValue) { }
	~ValueObject() override = default;
};

class VariableObject :
	public Object
{
public:
	VariableObject() :Object(ObjectType::TotalVariable) { }
	~VariableObject() override = default;
};

class OperatorObject :
	public Object
{
public:
	OperatorObject() :Object(ObjectType::Operator) { }
	~OperatorObject() override = default;
};

class TempObject :
	public Object
{
	std::string var_name_;
public:
	TempObject(const std::string& var_name)
		: Object(ObjectType::TEMP_OBJ)
	{
		var_name_ = var_name;
	}
	~TempObject() = default;
	string getName() const { return var_name_; }
};

class LongObject;
class DoubleObject;
class StringObject;
class BoolObject;
class TupleObject;
class ListObject;
class DictObject;
class MatchObject;

class LongObject :	public Object
{
	long value_;
public:
	LongObject(const long &_val) : Object(ObjectType::LongObj), value_(_val)
	{
		// std::cout << "Long " << value_ << std::endl;
	}
	~LongObject() = default;
	
	long get_val() { return value_; }

	Object * add (Object *) override;
	Object * minus (Object *) override;
	Object * multiply (Object *) override;
	Object * divide (Object *) override;

	Object * more_or_equal(Object *) override;
	Object * more(Object *) override;
	Object * less_or_equal(Object *) override;
	Object * less(Object *) override;

	Object * leftmove(Object *) override;
	Object * rightmove(Object *) override;

	Object * mod(Object *) override;
	Object * ByteAnd(Object *) override;
	Object * ByteOr(Object *) override;
	Object * Xor(Object *) override;

	Object * equal(Object *) override;
	Object * not_equal(Object *) override;

	Object * negative() override;

	void print() const { std::cout << value_ << std::endl; }
};


class DoubleObject : public Object {
	double value_;
public:
	DoubleObject(const double &_val) : Object(ObjectType::DoubleObj), value_(_val)
	{
		// std::cout <<"Double " << value_ << std::endl;
	}
	~DoubleObject() = default;
	
	double get_val() { return value_; }
	
	Object * add(Object *) override;
	Object * minus(Object *) override;
	Object * multiply(Object *) override;
	Object * divide(Object *) override;

	Object * more_or_equal(Object *) override;
	Object * more(Object *) override;
	Object * less_or_equal(Object *) override;
	Object * less(Object *) override;

	Object * rightmove(Object* right) override;
	Object * leftmove(Object* right) override;

	Object * mod(Object* obj) override;

	Object * equal(Object *)override;
	Object * not_equal(Object *)override;

	Object * negative() override;

	void print() const { std::cout << value_ << std::endl; }
};

class StringObject: public Object
{
	string value_;
public:
	StringObject(const string &_val) : Object(ObjectType::StringObj), value_(_val) {}
	~StringObject() = default;

	string get_val() { return value_; }

	Object * add(Object *) override;
	Object * mod(Object *) override;

	Object * equal(Object *) override;
	Object * not_equal(Object *)override;

	void print() const { std::cout << value_.substr(1, value_.length() - 2) << std::endl; }
};

class BoolObject: public Object
{
	bool value_;
public:
	BoolObject(bool value) :Object(BoolObj), value_(value)
	{
	}
	~BoolObject() = default;

	bool get_val() {
		return value_;
	}

	Object * And(Object *) override;
	Object * Or(Object *) override;
	Object * Not() override;

	Object * equal(Object *) override;
	Object * not_equal(Object *)override;

	void print() const
	{
		if (value_)
			std::cout << "True" << std::endl;
		else
			std::cout << "False" << std::endl;
	}
};

class ListObject: public Object
{
	vector<Object*> value_{};
public:
	void append(Object *);
	ListObject() :Object(ObjectType::ListObj) { }
	~ListObject() = default;

	vector<Object *> * get_val() {
		return &value_;
	}

	void print() const 
	{
		std::cout << "( ";
		auto it = value_.begin();
		for (; it != value_.end() - 1; ++it)
		{
			(*it)->print();
			std::cout << ", ";
		}
		(*it)->print();
		std::cout << " )" << std::endl;
			
	}
};
