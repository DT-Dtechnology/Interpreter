#pragma once
#include "Node.h"

/**
 * \brief 
 * 整体控制Object的建立过程。可以基于数据类型类型建立对应的Object类型
 * 本身为单件的工厂函数。
 */
class ObjectFactory
{
public:
	ObjectFactory() = default;
	~ObjectFactory() = default;
	static Object* createObject(Block*, const string& name);
	static Object* createObject(Block*, Node* list_node);
	static Object* getObject(Node* node);
};

