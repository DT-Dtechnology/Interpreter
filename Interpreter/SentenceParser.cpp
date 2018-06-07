#include "stdafx.h"
#include "SentenceParser.h"
#include "Object.h"
#include "Error.h"
#include "Matrix.h"
#include "SenDivider.h"

using std::stack;

Object* getObject(Block*, string, ObjectType);

void SentenceParser::divide()
{
	SenDivider* sen_divider = new SenDivider(sentence_->getOrder());
	word_queue_ = *sen_divider->work();
	delete sen_divider;
}

string getNodeMsg(const Word& word)
{
	if (word.getType() == WordType::value)
		return "var";
	else if (word.getType() == WordType::variable)
		//####
		//此处原本应该是value
		//但是，由于未出现value原因，特更改为variable
		return "var";
	else
		return word.getMsg();
}

void SentenceParser::buildTree()
{
	stack<Node*> ParseStack;
	Node* Root = new Node(NodeType::SEN);
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
		cout << "Row: " << nodeToInt[Top] << " Column: " << stringToInt[front] << endl;
		

			if (Top == NodeType::TERMINATE)
			{
				if (X->getValue()->getType() == ObjectType::TotalValue ||
					X->getValue()->getType() == ObjectType::TotalVariable)
				{
					// X 更新 Object 所指向的内容
					// 此处暂时存储为Total Object的特殊对象
					// 报错处理时要格外小心
					// ####

					//####
					//释放管理，在Varieble对应的Node上，isTemp为false，默认为true
					//用于表示不能删除

					ObjectType type = X->getValue()->getType();
					if (type == ObjectType::TotalValue)
						X->isTemp_ = true;
					X->value_ = getObject(cur_block_, word_queue_.front().getMsg(), type);
					word_queue_.pop();
					front = getNodeMsg(word_queue_.front());
				}
				else if (isTerminate[stringToChar[front]])
				{
					// isTerminate[] 表示终结符
					// stringToChar[] 表示终结符的转化
					const int tmp = stringToChar[front];
					// 终结符转NodeType 例如：+->ADD
					X->nodeType_ = charToNode[tmp];
					word_queue_.pop();
					front = getNodeMsg(word_queue_.front());
				}
				else
					throw Error("Wrong Match");
				cout << "Match" << endl << endl;
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
				//nodeToInt 行号
				//stringToInt 列好
				string magic_code = Matrix[nodeToInt[Top]][stringToInt[front]];

				cout << "Generating......" << endl;
				cout << "magic code:[ " << magic_code << "]" << endl;
				cout << "front: " << front << endl;
				cout << "Top: " << Top << endl;
				cout << "Row" << nodeToInt[Top] << "  Column" << stringToInt[front] << endl;

				cout << "Match Generation" << Matrix[nodeToInt[Top]][stringToInt[front]] << endl;
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

				cout << "Generate" << endl << endl;
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

Object* getObject(Block* cur_block, string name, ObjectType type = ObjectType::TotalValue)
{
	// ####
	if (type == ObjectType::TotalValue)
		return new TestObject(name);
	else
		return cur_block->searchObject(name);

	//####
	/*
	 * 此处允许返回空指针，在赋值语句中会判断是否为空指针，如果为空，则会
	 * 在Block中新建指针和添加Map，如果不为空，会直接修改存储于此处的指向对象
	 * 利用new和delete混用新建对象
	 */

	//####
	/*
	 * 对于回收临时指针问题,会在Node中记录指向对象的性质，
	 * 如果为临时对象，则析构
	 */
}
