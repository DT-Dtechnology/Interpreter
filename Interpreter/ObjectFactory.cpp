#include"stdafx.h"
#include"ObjectFactory.h"

Object*ObjectFactory::createObject(conststring&name)
{
	returnnewTestObject(name);
}
