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

string getNodeMsg(const Word& word)
{
	if (word.getType() == WordType::value)
		return "b";
	else if (word.getType() == WordType::variable)
		return "c";
	else
		return word.getMsg();
}

void SentenceParser::buildTree()
{
	stack<Node*> ParseStack;
	Node* Root = new Node(NodeType::ROOT);
	ParseStack.push(new Node(NodeType::END));
	ParseStack.push(Root);
	bool FLAG = true;
	word_queue_.push(Word(keyword, "#"));
	string front = getNodeMsg(word_queue_.front());
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
					X->value_ = getObject(cur_block_, word_queue_.front().getMsg());
					word_queue_.pop();
					front = getNodeMsg(word_queue_.front());
				}
				else if (isTerminate[stringToChar[front]])
				{
					const int tmp = stringToChar[front];
					X->nodeType_ = charToNode[tmp];
					word_queue_.pop();
					front = getNodeMsg(word_queue_.front());
				}
				else
					throw Error("Wrong Match");
				cout << "Match" << endl;
			}
			else if (Top == NodeType::END)
			{
				if (front == "#")
					FLAG = false;
				else
					throw Error("No END");
			}
			else if (Matrix[nodeToInt[Top]][stringToInt[front]] != "_")
			{
				string magic_code = Matrix[nodeToInt[Top]][stringToInt[front]];

				/*
				cout << magic_code << endl;
				cout << front << endl;
				*/

				cout << Matrix[nodeToInt[Top]][stringToInt[front]] << endl;
				// 顺序生成X的子节点
				for (auto i = 0; i < magic_code.length(); ++i)
				{
					if (magic_code[i] == '~')
						continue;
					if (isUnTerminate[magic_code[i]])
					{
						const NodeType type = charToNode[magic_code[i]];
						Node* node = new Node(type);
						X->addNode(node);
					}
					else if (isTerminate[magic_code[i]])
					{
						// 判断读入符号类型, 同时处理X结点的NodeType
						// 注意value 和 variable 不是 true
						// 基于对应的 chartoNode
						// ####
						Node* node = new Node(TERMINATE);
						node->setValue(new OperatorObject());
						X->addNode(node);
					}
					else
					{
						Node* node = new Node(NodeType::TERMINATE);
						if (word_queue_.front().getType() == WordType::variable)
							node->setValue(new VariableObject());
						else if (word_queue_.front().getType() == WordType::value)
							node->setValue(new ValueObject());
						else
							throw Error("Image");
						node->isLeaf_ = true;
						X->addNode(node);
					}
				}

				// 倒序入栈
				for (auto it = X->childVector_.end(); it != X->childVector_.begin();)
					ParseStack.push(*(--it));

				cout << "Generate" << endl;
			}
			else
				throw Error("What?");
		
		
	}
	cout << endl;
	cout << "Finish" << endl;
	cout << endl;
	root_ = Root;
}

void SentenceParser::parserNode(Node*)
{
	//####
}

void SentenceParser::work()
{
	divide();
	buildTree();
	parserRoot();
}

void SentenceParser::print_test_first()
{
	divide();
	while (!word_queue_.empty())
	{
		std::cout << word_queue_.front().getMsg() << "/";
		word_queue_.pop();
	}
	std::cout << std::endl;
}

void SentenceParser::print_test_second()
{
	divide();
	buildTree();
	cout << "Let Us Print." << endl;
	print_node(root_);
	std::cout << std::endl;
}

void SentenceParser::build_all()
{
	buildAll();
	printMatrix();
}

Object* getObject(Block*, string name)
{
	// ####
	return new TestObject(name);
}
