#include "stdafx.h"
#include "ObjectFactory.h"

Object* ObjectFactory::createObject(const string& name)
{
	return new TestObject(name);
}
