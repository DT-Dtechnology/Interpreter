#pragma once
#include "Node.h"

class Block;

/**
 * \brief 
 * ������õݹ���õķ�ʽ������ȫ���Ľ�㡣
 * ����ģʽ�����ڸ��������ѡ���Ӧ�ĺ����鲢�ӽڵ�
 * \return 
 * �Żع鲢�ӽڵ��Ľ��
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

