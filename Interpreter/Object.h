#pragma once
#include <iostream>

enum ObjectType
{
	DEBUG_TEST, TotalVariable, TotalValue, Operator
};

class Object
{
	ObjectType type_;
public:
	Object(ObjectType type) :type_(type) { }
	virtual ~Object() = default;
	ObjectType getType() const { return type_; }
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
	void print_test() const
	{
		std::cout << var_name_ << " ";
	}
};