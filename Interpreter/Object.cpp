#include "stdafx.h"
#include "Object.h"

Object* Object::add(Object* obj)
{
	cout << "I think you ......" << endl;
	system("pause");
	return nullptr;
}

Object* TestObject::add(Object* object)
{
	TestObject* newobject = dynamic_cast<TestObject*>(object);
	string add_name = " (EMPTY) ";
	if (object)
		add_name = newobject->getName();
	return new TestObject(var_name_ + add_name);
}

LongObject * LongObject::operator+(const LongObject *longobj) const
{
	return new LongObject(this->value_ + longobj->value_);
}

LongObject * LongObject::operator-(const LongObject *longobj) const
{
	return new LongObject(this->value_ - longobj->value_);
}

LongObject * LongObject::operator*(const LongObject *longobj) const
{
	return new LongObject(this->value_ * longobj->value_);
}

DoubleObject * LongObject::operator/(const LongObject *longobj) const
{
	return new DoubleObject(this->value_ / longobj->value_);
}