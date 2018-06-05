#pragma once
#include <vector>
#include "Object.h"

class Node;

typedef std::vector<Node*> NodeVector;

enum NodeType
{
	ROOT, END, TERMINATE, VALUE, VARIABLE,
	TEST_S, TEST_A, TEST_E, TEST_T, TEST_P, TEST_M, TEST_L, TEST_G, TEST_H, TEST_F,
	EQUAL, LEFT_BRACKET, RIGHT_BRACKET, ADD, MINUS, MULTIPLY, DIVIDE,
};

class Node
{
	Object* value_ = nullptr;
	Node* parent_ = nullptr;
	NodeVector childVector_;
	bool isLeaf_ = false;
	NodeType nodeType_;
	bool isTemp_ = false;
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
	if (node->getNodeType() == NodeType::ADD)
		std::cout << "+ " ;
	if (node->getNodeType() == NodeType::EQUAL)
		std::cout << "= " ;
	if (node->getNodeType() == NodeType::MULTIPLY)
		std::cout << "* " ;
	if (node->getNodeType() == NodeType::MINUS)
		std::cout << "- ";
	if (node->getNodeType() == NodeType::DIVIDE)
		std::cout << "/ ";
	if (node->getNodeType() == NodeType::LEFT_BRACKET)
		std::cout << "( " ;
	if (node->getNodeType() == NodeType::RIGHT_BRACKET)
		std::cout << ") " ;
	if (node->nodeType_ == NodeType::TERMINATE)
	{
		TestObject* tmp = dynamic_cast<TestObject*>(node->value_);
		if (tmp)
			tmp->print_test();
		else
			std::cout << "c ";
	}
	else
	{
		for (auto it = node->childVector_.begin(); it != node->childVector_.end(); ++it)
		{
			print_node(*it);
		}
	}
}


inline Node::~Node()
{
	for (auto it = childVector_.begin(); it != childVector_.end(); ++it)
		delete *it;
	if (isTemp_)
		delete value_;
}

inline Object* Node::getValue() const
{
	// ####
	return value_;
}
