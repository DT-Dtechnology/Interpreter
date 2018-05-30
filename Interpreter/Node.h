#pragma once
#include <vector>
#include "Object.h"

class Node;

typedef std::vector<Node*> NodeVector;

enum NodeType
{
	
};

class Node
{
	Object* value_;
	Node* parent_;
	NodeVector childVector_;
	bool isLeaf_;
	NodeType nodeType_;
public:
	Node();
	~Node();
	NodeType getNodeType() const;
	NodeVector* getChild() const;
};



Node::Node()
{
}


Node::~Node()
{
}
