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
	void print_test() const
	{
		std::cout << var_name_ << " ";
	}
};

class LongObject;
class DoubleObject;
class StringObject;
class BoolObject;
class TupleObject;
class ListObject;
class DictObject;

class LongObject :
	public Object
{
	long value_;
public:
	LongObject(const long &_val) : Object(ObjectType::LongObj), value_(_val) {}
	~LongObject() = default;
	LongObject* operator+(const LongObject* longobj) const;
	LongObject* operator-(const LongObject* longobj) const;
	LongObject* operator*(const LongObject* longobj) const;
	DoubleObject* operator/(const LongObject* longobj) const;

	//
};


class DoubleObject : public Object {
	double value_;
public:
	DoubleObject(const double &_val) : Object(ObjectType::DoubleObj), value_(_val) {}
	~DoubleObject() = default;

};

class StringObject: public Object
{
	string value_;
public:
	StringObject(const string &_val) : Object(ObjectType::StringObj), value_(_val) {}
	~StringObject() = default;

};

class BoolObject: public Object
{
	bool value_;
public:
	BoolObject(bool value) :Object(BoolObj), value_(value) { }
	~BoolObject() = default;
};

class ListObject: public Object
{
	vector<Object*> value_{};
public:
	ListObject():Object(ObjectType::ListObj){}
	~ListObject() = default;

};