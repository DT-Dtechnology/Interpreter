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
		// 重新设置node的value_
		// 这里应该是用到工厂函数重新处理Object*
		// 此处需要更改node的类型至Value或Variable
		// 
			obj = ObjectFactory::createObject(cur, node);
			new_node = new Node(NodeType::VALUE);
			new_node->setValue(obj);
			if (!obj)
				throw Error("I do not know ");
			return new_node;
		case VARIABLE:
			//无需处理
			//暂时没有
			//由于控制手段有其他方法，可能会被废除
			return node;
		case VALUE:
			return node;

		case ADD:
			return addFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case MULTIPLY:
			return multiFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case MINUS:
			return minusFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case DIVIDE:
			return divideFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		
		case MOD:
			return modFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		
		case AND:
			return andFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case OR:
			return orFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));

		case SMALLER:
			return lessFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case BIGGER:
			return moreFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case SMALLER_OR_EQUAL:
			return leeqFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case BIGGER_OR_EQUAL:
			return moeqFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		
		case IS_EQUAL:
			return equalFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case IS_NOT_EQUAL:
			return nequalFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));

		case LEFT_MOVE:
			return leftFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		case RIGHT_MOVE:
			return rightFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));

		case EQUAL:
			return assFunc(FuncSwitcher(cur, node->childVector_[0]), FuncSwitcher(cur, node->childVector_[1]));
		
		case NEGA:
			return negeFunc(FuncSwitcher(cur, node->childVector_[0]));
		case POSI:
			return posiFunc(FuncSwitcher(cur, node->childVector_[0]));

		case LISTFLAG:
		// We should return a node with a list object here.
			// ############
			// BIG ERROR 建立无数次单个元素的List
			obj = ObjectFactory::createObject(cur, node);
			new_node = new Node(NodeType::VALUE);
			new_node->setValue(obj);
			if (!obj)
				throw Error("I do not know ");
			return new_node;

		case IF:
			new_node = new Node(NodeType::IF);
			new_node->setValue(FuncSwitcher(cur, node->childVector_[0])->getValue());
			return new_node;

		case ELIF:
			new_node = new Node(NodeType::IF);
			new_node->setValue(FuncSwitcher(cur, node->childVector_[1])->getValue());
			return new_node;

		case ELSE:
			new_node = new Node(NodeType::IF);
			new_node->setValue(new BoolObject(true));
			return new_node;
		// ######
		// 注意LOOP的两种类型
		// 需要条件判断

		default: 
			return FuncSwitcher(cur, node->childVector_[0]);
	}
}

// 此处使用策略模式


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
Node* divideFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->divide(rightobj));
	return node;
}
Node* minusFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->minus(rightobj));
	return node;
}
Node* modFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->mod(rightobj));
	return node;
}


Node* andFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->And(rightobj));
	return node;
}
Node* orFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->Or(rightobj));
	return node;
}

Node* lessFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->less(rightobj));
	return node;
}
Node* moreFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->more(rightobj));
	return node;
}
Node* moeqFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->more_or_equal(rightobj));
	return node;
}
Node* leeqFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->less_or_equal(rightobj));
	return node;
}

Node* equalFunc(Node *left, Node *right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->equal(rightobj));
	return node;
}
Node* nequalFunc(Node *left, Node *right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->not_equal(rightobj));
	return node;
}
Node* leftFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->leftmove(rightobj));
	return node;
}
Node* rightFunc(Node* left, Node* right)
{
	Node* node = new Node(NodeType::VALUE);
	Object* leftobj = left->getValue();
	Object* rightobj = right->getValue();
	node->setValue(leftobj->rightmove(rightobj));
	return node;
}

Node* posiFunc(Node* node)
{
	node->setNodeType(VALUE);
	return node;
}
Node* negeFunc(Node* node)
{
	// ######
	node->setNodeType(VALUE);
	node -> setValue(node->getValue() -> negative());
	return node;
}
Node* notFunc(Node* node)
{
	node->setNodeType(VALUE);
	node->getValue() -> Not();
	return node;
}


Node* assFunc(Node* left, Node* right)
{
	if (left->getValue()->getType() != ObjectType::ListObj)
	{
		cout << "Assign, Then value: ";
		const string name = left->getValue()->getName();
		Block* cur = left->getValue()->get_block();
		string tmp_name;
		Block* tmp_block = nullptr;
		if (!right->getValue()->get_block())
		{
			right->getValue()->setBlock(cur);
			right->getValue()->setName(name);
		}
		else
		{
			tmp_name = right->getValue()->getName();
			tmp_block = right->getValue()->get_block();
			right->getValue()->setBlock(cur);
			right->getValue()->setName(name);
		}
		cur->changeVar(name, right->getValue());
		if (tmp_block)
		{
			right->getValue()->setBlock(tmp_block);
			right->getValue()->setName(tmp_name);
		}
		cout << name << " ";
		right->getValue()->print_test();
	}
	else
	{
		cout << "List Assign" << endl;
		vector<Object*>* left_list = (dynamic_cast<ListObject*>(left->getValue()))->get_val();
		vector<Object*>* right_list = (dynamic_cast<ListObject*>(right->getValue()))->get_val();
		auto left_it = left_list->begin();
		auto right_it = right_list->begin();
		while(left_it != left_list->end())
		{
			Node* left_node = new Node;
			Node* right_node = new Node;
			left_node->setValue(*left_it);
			right_node->setValue(*right_it);
			assFunc(left_node, right_node);
			++left_it;
			++right_it;
		}
		if (right_it != right_list->end())
			throw Error("Wrong size of equal");
	}
	return right;
}
