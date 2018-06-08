#include "stdafx.h"
#include "ObjectFactory.h"

inline bool isVar(const string& name)
{
	return name[0] == '_' || (name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z');
}

Object* ObjectFactory::createObject(const string& name)
{
	if (name.length() == 0)
		return nullptr;
}
