#include "stdafx.h"
#include "ParseFuncSwitcher.h"
#include "ObjectFactory.h"

Node* FuncSwitcher(Block* cur, Node* node)
{
	//cout << node->getNodeType() << endl;
	//system("pause");
	Object* obj;
	Node* new_node = new Node;
	switch (node->getNodeType())
	{
		case TERMINATE:
		// ��������node��value_
		// ����Ӧ�����õ������������´���Object*
		// �˴���Ҫ����node��������Value��Variable
		// 
			obj = ObjectFactory::createObject(cur, node);
			new_node = new Node(NodeType::VALUE);
			new_node->setValue(obj);
			return new_node;
		
		case VARIABLE:
			//���账��
			//��ʱû��
			//���ڿ����ֶ����������������ܻᱻ�ϳ�
			return node;

		case VALUE:
			return node;

		case ADD:
			return addFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case MULTIPLY:
			return multiFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case EQUAL:
			return assFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case LISTFLAG:
		// We should return a node with a list object here.
			return nullptr;
		
		default: 
			return FuncSwitcher(cur, node->childVector_[0]);
	}
}

// �˴�����ʹ�ò���ģʽ


Node* addFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->add(rightobj));
	return node;
}

Node* multiFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->multiply(rightobj));
	return node;
}

Node* assFunc(Node* left, Node* right)
{
	left->setValue(right->getValue());
	return right;
}
