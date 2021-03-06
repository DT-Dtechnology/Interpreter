#include "stdafx.h"
#include "ParseFuncSwitcher.h"
#include "ObjectFactory.h"

Node* FuncSwitcher(Block* cur, Node* node)
{
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
			return addFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case MULTIPLY:
			return multiFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case MINUS:
			return minusFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case DIVIDE:
			return divideFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		
		case MOD:
			return modFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		
		case AND:
			return andFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case OR:
			return orFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));

		case SMALLER:
			return lessFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case BIGGER:
			return moreFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case SMALLER_OR_EQUAL:
			return leeqFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case BIGGER_OR_EQUAL:
			return moeqFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		
		case IS_EQUAL:
			return equalFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case IS_NOT_EQUAL:
			return nequalFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));

		case LEFT_MOVE:
			return leftFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		case RIGHT_MOVE:
			return rightFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));

		case EQUAL:
			return assFunc(FuncSwitcher(cur, node->childVector_[1]), FuncSwitcher(cur, node->childVector_[0]));
		
		case NEGA:
			return negeFunc(FuncSwitcher(cur, node->childVector_[0]));
		case POSI:
			return posiFunc(FuncSwitcher(cur, node->childVector_[0]));

		case LISTFLAG:
		// We should return a node with a list object here.
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
		
		case WHILE:
			new_node = new Node(NodeType::LOOP);
			new_node->setValue(FuncSwitcher(cur, node->childVector_[1])->getValue());
			return new_node;

		case FOR:
		{
			new_node = new Node(NodeType::LOOP);
			Node* left_node = FuncSwitcher(cur, node->childVector_[1]);
			Node* right_node = FuncSwitcher(cur, node->childVector_[2]);
			if(left_node->getValue()->list_posi == -1)
			{
				if (right_node->getValue()->getType() != ListObj)
				{
					right_node->getValue()->list_posi = 0;
					assFunc(left_node, right_node);
				}
				else
				{
					ListObject* list_object = dynamic_cast<ListObject*>(right_node->getValue());
					Node* new_right_node = new Node(VALUE);
					new_right_node->setValue((*list_object->get_val())[0]);
					new_right_node->getValue()->list_posi = 0;
					assFunc(left_node, new_right_node);
				}
				Node* new_tmp_node = new Node(LOOP);
				new_tmp_node->setValue(new BoolObject(true));
				
				return new_tmp_node;
			}else
			{
				if (right_node->getValue()->getType() != ListObj)
				{
					Node* new_tmp_node = new Node(LOOP);
					new_tmp_node->setValue(new BoolObject(false));
					left_node->getValue()->list_posi = -1;
					return new_tmp_node;
				}
				ListObject* list_object = dynamic_cast<ListObject*>(right_node->getValue());
				if(left_node->getValue()->list_posi >= list_object->get_val()->size()-1)
				{
					Node* new_tmp_node = new Node(LOOP);
					new_tmp_node->setValue(new BoolObject(false));
					left_node->getValue()->list_posi = -1;
					return new_tmp_node;
				}
				Node* new_right_node = new Node(VALUE);
				new_right_node->setValue((*list_object->get_val())[left_node->getValue()->list_posi+1]);
				new_right_node->getValue()->list_posi = left_node->getValue()->list_posi+1;
				assFunc(left_node, new_right_node);
				Node* new_tmp_node = new Node(LOOP);
				new_tmp_node->setValue(new BoolObject(true));
				return new_tmp_node;
			}
		}
		
		case DEF:
			{
			const string name = FuncSwitcher(cur, node->childVector_[0])->getValue()->getName();
			vector<string> name_list;
			if(node->childVector_.size() != 1)
			{
				Node *childNode = FuncSwitcher(cur, node->childVector_[1]);
				ListObject *list = dynamic_cast<ListObject*>(childNode->getValue());
				if (list)
				{
					for (auto it = list->get_val()->begin(); it != list->get_val()->end(); ++it)
					{
						name_list.push_back((*it)->getName());
					}
				}else
				{
					name_list.push_back(childNode->getValue()->getName());
				}
			}
			cur->addFunc(name, name_list);
			//
			Traveller traveller(cur, cur->searchFunc(name));
			
			Node* tmp_node = new Node(DEF);
			Object* object = new Object(FuncObj);
			object->setName(name);
			tmp_node->setValue(object);
			return tmp_node;
			}

		case RETURN:
			new_node->setNodeType(RETURN);
			if (node->childVector_.size() == 1)
				node->setValue(nullptr);
			else
				new_node->setValue(FuncSwitcher(cur, node->childVector_[1])->getValue());
			return new_node;

		case FUNC:
			{
			
			new_node->setNodeType(VALUE);
			const string name = FuncSwitcher(cur, node->childVector_[0])->getValue()->getName();
			if(name == "range")
			{
				ListObject* list_object = new ListObject();
				if (node->childVector_.size() == 2)
				{
					Node* list_node = FuncSwitcher(cur, node->childVector_[1]);
					Object* tmp_obj = list_node->getValue();
					int startnum, endnum;
					if (tmp_obj->getType() != ListObj)
					{
						LongObject* tmp = dynamic_cast<LongObject*>(tmp_obj);
						startnum = 0;
						endnum = tmp->get_val();
						delete tmp;
					}
					else
					{
						auto tmp = *dynamic_cast<ListObject*>(tmp_obj)->get_val();
						LongObject* long_obj = dynamic_cast<LongObject*>(tmp[0]);
						startnum = long_obj->get_val();
						long_obj = dynamic_cast<LongObject*>(tmp[1]);
						endnum = long_obj->get_val();
						delete long_obj;
					}
					ListObject* list = new ListObject;
					for(auto it = startnum ; it < endnum ; ++it)
					{
						list->append(new LongObject(it));
					}
					new_node->setValue(list);
					return new_node;
				}
					throw Error("Wrong Range Function Paraments");
			}
			Block* block = cur->searchFunc(name);
			if(node->childVector_.size() == 1)
			{
				Traveller tmp_traveller = Traveller(block);
				tmp_traveller.work();
				new_node->setValue(block->return_value());
			}else if(node->childVector_.size() == 2)
			{
				Node* list_node = FuncSwitcher(cur,node->childVector_[1]);
				Object* tmp_obj = list_node->getValue();
				vector<Object*> obj_vec;
				if(tmp_obj->getType() != ListObj)
				{
					obj_vec.push_back(tmp_obj);
				}else
				{
					ListObject* list_object = dynamic_cast<ListObject*>(tmp_obj);
					for (auto it = list_object->get_val()->begin();
						it != list_object->get_val()->end(); ++it)
						obj_vec.push_back(*it);
				}
				block->setValue(obj_vec);
				Traveller tmp_traveller = Traveller(block);
				tmp_traveller.work();
				new_node->setValue(block->return_value());
			}
			else
				throw Error("Unkown Error we can't hold");
			return new_node;
			}
		case PRINT:
			return printFunc(FuncSwitcher(cur, node->childVector_[1]));

		default: 
			if (node->childVector_.size() != 0)
				return FuncSwitcher(cur, node->childVector_[0]);
			cout << node->getNodeType() << endl;
			throw Error("I think you have not input anything");
			return new Node(node->getNodeType());
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

	}
	else
	{
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

Node* printFunc(Node* node)
{
	node->getValue()->print();
	cout << endl;
	return node;
}