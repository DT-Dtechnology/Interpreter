#pragma once
#include "Node.h"

class Block;

Node* FuncSwitcher(Block*, Node*);

Node* addFunc(Node*, Node*);
Node* multiFunc(Node*, Node*);
Node* minusFunc(Node*, Node*);
Node* divideFunc(Node*, Node*);
Node* modFunc(Node*, Node*);
Node* zhengFunc(Node*, Node*);
Node* andFunc(Node*, Node*);
Node* orFunc(Node*, Node*);

Node* lessFunc(Node*, Node*);
Node* moreFunc(Node*, Node*);
Node* moeqFunc(Node*, Node*);
Node* leeqFunc(Node*, Node*);
Node* equalFunc(Node*, Node*);
Node* nequalFunc(Node*, Node*);

Node* leftFunc(Node*, Node*);
Node* rightFunc(Node*, Node*);

Node* posiFunc(Node*);
Node* negeFunc(Node*);
Node* notFunc(Node*);

Node* assFunc(Block*, Node*, Node*);

