#pragma once
#include "Node.h"

class Block;

/**
 * \brief 
 * 整体采用递归调用的方式来遍历全部的结点。
 * 策略模式，基于父结点类型选择对应的函数归并子节点
 * \return 
 * 放回归并子节点后的结果
 */
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

Node* assFunc(Node*, Node*);

Node* printFunc(Node*);

