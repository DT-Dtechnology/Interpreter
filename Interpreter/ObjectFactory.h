#pragma once
#include "Object.h"
class ObjectFactory
{
public:
	ObjectFactory() = default;
	~ObjectFactory() = default;
	static Object* createObject(const string& name);
};

