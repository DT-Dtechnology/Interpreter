#pragma once
#include "Node.h"

/**
 * \brief 
 * �������Object�Ľ������̡����Ի��������������ͽ�����Ӧ��Object����
 * ����Ϊ�����Ĺ���������
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

