#include "stdafx.h"
#include "Object.h"

Object* Object::add(Object* obj)
{
	cout << "I think you ......" << endl;
	system("pause");
	return nullptr;
}

Object* Object::multiply(Object* obj)
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

Object* LongObject::add(Object* obj)
{
	cout << value_ << " Add ";
	obj->print_test();
	cout << endl;
	return this;
}

Object* LongObject::multiply(Object* obj)
{
	cout << value_ << " Multi ";
	obj->print_test();
	cout << endl;
	return this;
}

void LongObject::print_test() const
{
	cout << value_;
}

