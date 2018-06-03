#include "stdafx.h"
#include "SentenceParser.h"
#include "Object.h"
#include "Error.h"
#include "Matrix.h"
#include "SenDivider.h"

using std::stack;

Object* getObject(Block*, string);

void SentenceParser::divide()
{
	SenDivider* sen_divider = new SenDivider(sentence_->getOrder());
	word_queue_ = *sen_divider->work();
	delete sen_divider;
}

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

		if (Top == NodeType::TERMINATE)
		{
			if (X->getValue()->getType() == ObjectType::TotalValue ||
				X->getValue()->getType() == ObjectType::TotalVariable)
			{
				// X 更新 Object 所指向的内容
				// 此处暂时存储为Total Object的特殊对象
				// 报错处理时要格外小心
				// ####
				X->value_ = getObject(cur_block_, front);
				word_queue_.pop();
				front = word_queue_.front().getMsg();
			}
			else if (isTerminate[stringToChar[front]])
			{
				word_queue_.pop();
				front = word_queue_.front().getMsg();
			}
			else
				throw Error();
		}
		else if (Top == NodeType::END)
		{
			if (front == "#")
				FLAG = false;
			else
				throw Error();
		}
		else if (Matrix[nodeToInt[Top]][stringToChar[front]] != "_")
		{
			string magic_code = Matrix[nodeToInt[Top]][stringToChar[front]];

			// 顺序生成X的子节点
			for (auto i = 0; i < magic_code.length(); ++i)
			{
				if (isUnTerminate[magic_code[i]])
				{
					const NodeType type = charToNode[magic_code[i]];
					Node* node = new Node(type);
					X->addNode(node);
				}
				else if(isTerminate[magic_code[i]])
				{
					// 判断读入符号类型, 同时处理X结点的NodeType
					// 注意value 和 variable 不是 true
					// 基于对应的 chartoNode
					// ####
					X->nodeType_ = charToNode[magic_code[i]];
				}
				else
				{
					Node* node = new Node(NodeType::TERMINATE);
					if (word_queue_.front().getType() == WordType::variable)
						node->setValue(new VariableObject());
					else if (word_queue_.front().getType() == WordType::value)
						node->setValue(new ValueObject());
					else
						throw Error();
					node->isLeaf_ = true;
					X->addNode(node);
				}
			}

			// 倒序入栈
			for(auto it = X->childVector_.end()-1; it >= X->childVector_.begin(); --it)
				ParseStack.push(*it);

		}
		else
			throw Error();
	}
	root_ = Root;
}

void SentenceParser::parserNode(Node*)
{
	//####
}

void SentenceParser::print_test_first()
{
	divide();
	while (!word_queue_.empty())
	{
		std::cout << word_queue_.front().getMsg() << " ";
		word_queue_.pop();
	}
}

Object* getObject(Block*, string)
{
	// ####
	return nullptr;
}
