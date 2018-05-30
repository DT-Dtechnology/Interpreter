#pragma once

enum ObjectType
{
	TotalVariable, TotalValue
};

class Object
{
	ObjectType type_;
public:
	Object(ObjectType type) :type_(type) { }
	virtual ~Object() = 0;
	ObjectType getType() const { return type_; }
};

class ValueObject:
	public Object
{
public:
	ValueObject() :Object(ObjectType::TotalValue) { }
	~ValueObject() override = default;
};

class VariableObject:
	public Object
{
public:
	VariableObject() :Object(ObjectType::TotalVariable) { }
	~VariableObject() override = default;
};