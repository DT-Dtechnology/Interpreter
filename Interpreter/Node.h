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
	Object* getValue();
	void addNode(Node* node) { childVector_.push_back(node); }
	void setValue(Object* object) { value_ = object; }

	friend class SentenceParser;
};

inline Object* Node::getValue()
{
	// ####
	return nullptr;
}
