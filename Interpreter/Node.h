#pragma once
#include <vector>
#include "Object.h"

class Node;

typedef std::vector<Node*> NodeVector;

enum NodeType
{
	ROOT, END, TERMINATE, VALUE, VARIABLE,
	TEST_S, TEST_A, TEST_E, TEST_T, TEST_P, TEST_M, TEST_L,
	EQUAL, LEFT_BRACKET, RIGHT_BRACKET, ADD, MINUS, MULTIPLY, DIVIDE,
};

class Node
{
	Object* value_ = nullptr;
	Node* parent_ = nullptr;
	NodeVector childVector_;
	bool isLeaf_ = false;
	NodeType nodeType_;
public:
	Node();
	~Node();
	Node(NodeType nodeType) :nodeType_(nodeType) {}
	NodeType getNodeType() const { return nodeType_; };
	NodeVector* getChild() { return &childVector_; }
	Object* getValue() const;
	void addNode(Node* node) { childVector_.push_back(node); }
	void setValue(Object* object) { value_ = object; }

	friend class SentenceParser;
	friend void print_node(Node*);
};

inline void print_node(Node* node)
{
	if (node->nodeType_ == NodeType::TERMINATE)
	{
		TestObject* tmp = dynamic_cast<TestObject*>(node->value_);
		tmp->print_test();
	}
	else
	{
		for (auto it = node->childVector_.begin(); it != node->childVector_.end(); ++it)
		{
			print_node(*it);
		}
		std::cout << std::endl;
	}
}


inline Object* Node::getValue() const
{
	// ####
	return value_;
}
