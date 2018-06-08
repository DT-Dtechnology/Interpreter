#include "stdafx.h"
#include "ParseFuncSwitcher.h"

Node* FuncSwitcher(Block* cur, Node* node)
{
	cout << node->getNodeType() << endl;
	//system("pause");
	switch (node->getNodeType())
	{
		case TERMINATE:
		// 重新设置node的value_
		// 这里应该是用到工厂函数重新处理Object*
		// 此处需要更改node的类型至Value或Variable
		// 
			return node;
		
		case VARIABLE:
			//无需处理
			return node;

		case VALUE:
			return node;

		case ADD:
			return addFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		
		case EQUAL:
			return assFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case LISTFLAG:
		// We should return a node with a list object here.
			return nullptr;
		
		default: 
			return FuncSwitcher(cur, node->childVector_[0]);
	}
}

Node* addFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->add(rightobj));
	return node;
}

Node* assFunc(Node* left, Node* right)
{
	left->getValue()->print_test();
	cout << "= ";
	right->getValue()->print_test();
	cout << endl << endl;
	system("pause");
	return right;
}
