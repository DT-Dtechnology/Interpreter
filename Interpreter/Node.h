#pragma once
#include <vector>
#include "Object.h"

class Node;

typedef std::vector<Node*> NodeVector;

enum NodeType
{
	ROOT, END, TERMINATE, VALUE, VARIABLE,
	EXP, SEN, ASS, LOOP, EXPL, EXPLL, DEF, FUNC, DEFF,
	EE, T, TT, F, FF, G, GG, H, HH, K, X,
	VARL, VARLL, IF, JUMP, PRINT, PRINTT,
	EQUAL, LEFT_BRACKET, RIGHT_BRACKET, ADD, MINUS, MULTIPLY, DIVIDE, IS_EQUAL, IS_NOT_EQUAL,
	LEFT_MOVE, RIGHT_MOVE, WHILE, FOR, IN, COLON, COMMA, NOT, BANG, PLUS_PLUS, MINUS_MINUS,
	ELIF, ELSE, CONTINUE, BREAK, PASS, RETURN, PARAL, PARALL, PARA
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

inline Node::~Node()
{
	for (auto it = childVector_.begin(); it != childVector_.end(); ++it)
		delete *it;
	delete value_;
}

inline Object* Node::getValue() const
{
	// ####
	return value_;
}
