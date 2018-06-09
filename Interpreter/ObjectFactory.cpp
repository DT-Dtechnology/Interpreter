#include "stdafx.h"
#include "ObjectFactory.h"
#include "ParseFuncSwitcher.h"

inline bool isVar(const string& name)
{
	return name[0] == '_' || (name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z');
}

inline bool isDouble(const string& name)
{
	for(int i = 0 ; i < name.length() ; ++i)
	{
		if(name[i] == '.')
		{
			if (i + 1 == name.length())
				return false;
			return true;
		}
	}
	return false;
}

inline bool isString(const string& name)
{
	return (name[0] == '\'' || name[0] == '\"');
}

Object* ObjectFactory::createObject(Block* cur, const string& name)
{
	if (name.length() == 0)
		return nullptr;
	if (name == "True")
		return new BoolObject(true);
	if (name == "False")
		return new BoolObject(false);
	if (isVar(name))
	{
		Object* node = new Object(ObjectType::TotalValue);
		
	}
	if (isString(name))
		return new StringObject(name);
	if (isDouble(name))
	{
		const double value = std::stod(name);
		return new DoubleObject(value);
	}
	const long value = std::stol(name);
	return new LongObject(value);
}

Object* ObjectFactory::createObject(Block* cur, Node* all_node)
{
	ListObject* list = new ListObject;
	if(all_node->getNodeType() == TERMINATE)
	{
		TempObject* tmp = dynamic_cast<TempObject*>(all_node->getValue());
		const string value = tmp->getName();
		Object * obj = ObjectFactory::createObject(cur, value);
		return obj;
	}
	if (all_node->getNodeType() == VALUE || all_node->getNodeType() == VARIABLE)
		return getObject(all_node);
	if(all_node->getNodeType() != LISTFLAG)
		return nullptr;
	NodeVector* child_list = all_node->getChild();
	for (auto it = child_list->begin(); it != child_list->end(); ++it)
	{
		Node* temp_node = FuncSwitcher(cur, *it);
		list->append(temp_node->getValue());
	}
	return list;
}

Object* ObjectFactory::getObject(Node* node)
{
	return node->getValue();
}
