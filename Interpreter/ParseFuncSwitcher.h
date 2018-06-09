#pragma once
#include "Node.h"

class Block;

Node* FuncSwitcher(Block*, Node*);

Node* addFunc(Node*, Node*);

Node* multiFunc(Node*, Node*);

Node* assFunc(Node*, Node*);