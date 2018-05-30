#include "stdafx.h"
#include "SentenceParser.h"
#include "Object.h"
#include "Error.h"

using std::stack;

Object* getObject(Block*, string);

void SentenceParser::buildTree()
{
	stack<Node*> ParseStack;
	Node* Root = new Node(NodeType::ROOT);
	ParseStack.push(new Node(NodeType::END));
	ParseStack.push(Root);
	bool FLAG = true;
	string front = word_queue_.front().getMsg();
	while (FLAG)
	{
		auto X = ParseStack.top();
		ParseStack.pop();
		NodeType Top = X->getNodeType();

		if( Top == NodeType::TERMINATE)
		{
			if (X->getValue()->getType() == ObjectType::TotalValue ||
				X->getValue()->getType() == ObjectType::TotalVariable)
			{
				// X 更新 Object 所指向的内容
				// 此处暂时存储为Total Object的特殊对象
				// 报错处理时要格外小心
				word_queue_.pop();
				front = word_queue_.front().getMsg();
			}
			else if (X->getValue() == getObject(cur_block_, front))
			{
				word_queue_.pop();
				front = word_queue_.front().getMsg();
			}
			else
				throw Error();
		}
		else if( Top == NodeType::END)
		{
			if (front == "#")
				FLAG = false;
			else
				throw Error();
		}
		else if ()
	}
}
