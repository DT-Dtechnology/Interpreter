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
	word_queue_.push(Word(keyword, "#"));
	string front = word_queue_.front().getMsg();
	while (FLAG)
	{
		auto X = ParseStack.top();
		ParseStack.pop();
		NodeType Top = X->getNodeType();

		cout << endl;
		cout << "Type " << Top << endl;
		cout << "Front " << front << endl;
		cout << Matrix[nodeToInt[Top]][stringToInt[front]] << endl;

		
		if (Top == NodeType::TERMINATE)
		{
			if (isTerminate[stringToChar[front]])
			{
				word_queue_.pop();
				front = word_queue_.front().getMsg();	//�˴����ڱ���
				ParseStack.push(X);

				cout << "Match" << endl;
			}
			if (X->getValue()->getType() == ObjectType::TotalValue ||
				X->getValue()->getType() == ObjectType::TotalVariable)
			{
				// X ���� Object ��ָ�������
				// �˴���ʱ�洢ΪTotal Object���������
				// ������ʱҪ����С��
				// ####
				X->value_ = getObject(cur_block_, front);
				word_queue_.pop();
				front = word_queue_.front().getMsg();
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
			
			cout << magic_code << endl;
			cout << front << endl;
			// ˳������X���ӽڵ�
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
				else if(isTerminate[magic_code[i]])
				{
					// �ж϶����������, ͬʱ����X����NodeType
					// ע��value �� variable ���� true
					// ���ڶ�Ӧ�� chartoNode
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
						throw Error("Image");
					node->isLeaf_ = true;
					X->addNode(node);
				}
			}

			// ������ջ
			for(auto it = X->childVector_.end(); it != X->childVector_.begin();)
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
