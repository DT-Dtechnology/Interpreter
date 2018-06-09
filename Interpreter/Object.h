#pragma once
#include <iostream>
#include <vector>

using std::string;
using std::vector;

enum ObjectType
{
	DEBUG_TEST, TotalVariable, TotalValue, Operator, LongObj,
	DoubleObj, StringObj, TupleObj, ListObj, DictObj,
	BoolObj
};

class Object
{
	ObjectType type_;
	bool isTemp_ = false;

public:
	Object(ObjectType type) :type_(type) { }
	virtual ~Object() = default;

	ObjectType getType() const { return type_; }
	void setTemp() { isTemp_ = true; }
	bool getStatus() const { return isTemp_; }
	virtual void print_test() const { std::cout << "Test" << std::endl; }

	double get_val();


	virtual Object * add(Object *obj);
	virtual Object * minus(Object *obj);
	virtual Object * multiply(Object *obj);
	virtual Object * divide(Object *obj);

	virtual Object * more_or_equal(Object *obj);
	virtual Object * more(Object *obj);
	virtual Object * less_or_equal(Object *obj);
	virtual Object * less(Object *obj);

	virtual Object * leftmove(Object *obj);
	virtual Object * rightmove(Object *obj);

	virtual Object * mod(Object *obj);

	virtual Object * And(Object *obj);
	virtual Object * Or (Object *obj);
	virtual Object * Not();

	virtual Object * ByteAnd(Object * obj);
	virtual Object * ByteOr(Object * Obj);
	virtual Object * Xor(Object * Obj);

	
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

class TestObject :
	public Object
{
	std::string var_name_;
public:
	TestObject(const std::string& var_name)
		: Object(ObjectType::DEBUG_TEST)
	{
		var_name_ = var_name;
	}
	~TestObject() = default;
	void print_test() const override
	{
		std::cout << var_name_ << " ";
	}
	string getName() const { return var_name_; }
	Object* add(Object* object) override;
};

class LongObject;
class DoubleObject;
class StringObject;
class BoolObject;
class TupleObject;
class ListObject;
class DictObject;

class LongObject :	public Object
{
	long value_;
public:
	LongObject(const long &_val) : Object(ObjectType::LongObj), value_(_val) {}
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

	Object * leftmove(Object *);
	Object * rightmove(Object *);

	Object * mod(Object *);
	Object * ByteAnd(Object *);
	Object * ByteOr(Object *);
	Object * Xor(Object *);
};


class DoubleObject : public Object {
	double value_;
public:
	DoubleObject(const double &_val) : Object(ObjectType::DoubleObj), value_(_val) {}
	~DoubleObject() = default;
	
	double get_val() { return value_; }
	
	Object * add(Object *);
	Object * minus(Object *);
	Object * multiply(Object *);
	Object * divide(Object *);

	Object * more_or_equal(Object *) override;
	Object * more(Object *) override;
	Object * less_or_equal(Object *) override;
	Object * less(Object *) override;
};

class StringObject: public Object
{
	string value_;
public:
	StringObject(const string &_val) : Object(ObjectType::StringObj), value_(_val) {}
	~StringObject() = default;

	string get_val() { return value_; }

	Object * add(Object *);
	Object * mod(Object *);

};

class BoolObject: public Object
{
	bool value_;
public:
	BoolObject(bool value) :Object(BoolObj), value_(value) { }
	~BoolObject() = default;

	bool get_val() {
		return value_;
	}

	Object * And(Object *);
	Object * Or(Object *);
	Object * Not();
};

class ListObject: public Object
{
	vector<Object*> value_{};
public:
	void append(Object *);
	ListObject():Object(ObjectType::ListObj){}
	~ListObject() = default;

	vector<Object *> * get_val() {
		return &value_;
	}

	//for test
	ListObject(vector<Object*> temp_):Object(ObjectType::ListObj) {
		value_.assign(temp_.begin(), temp_.end());
	}
};
