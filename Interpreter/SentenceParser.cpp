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
		//�˴�ԭ��Ӧ����value
		//���ǣ�����δ����valueԭ���ظ���Ϊvariable
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
					// X ���� Object ��ָ�������
					// �˴���ʱ�洢ΪTotal Object���������
					// ������ʱҪ����С��
					// ####

					//####
					//�ͷŹ�����Varieble��Ӧ��Node�ϣ�isTempΪfalse��Ĭ��Ϊtrue
					//���ڱ�ʾ����ɾ��

					ObjectType type = X->getValue()->getType();
					if (type == ObjectType::TotalValue)
						X->isTemp_ = true;
					X->value_ = getObject(cur_block_, word_queue_.front().getMsg(), type);
					word_queue_.pop();
					front = getNodeMsg(word_queue_.front());
				}
				else if (isTerminate[stringToChar[front]])
				{
					// isTerminate[] ��ʾ�ս��
					// stringToChar[] ��ʾ�ս����ת��
					const int tmp = stringToChar[front];
					// �ս��תNodeType ���磺+->ADD
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
				//nodeToInt �к�
				//stringToInt �к�
				string magic_code = Matrix[nodeToInt[Top]][stringToInt[front]];

				cout << "Generating......" << endl;
				cout << "magic code:[ " << magic_code << "]" << endl;
				cout << "front: " << front << endl;
				cout << "Top: " << Top << endl;
				cout << "Row" << nodeToInt[Top] << "  Column" << stringToInt[front] << endl;

				cout << "Match Generation" << Matrix[nodeToInt[Top]][stringToInt[front]] << endl;
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
					else if (isTerminate[magic_code[i]])
					{
						// �ж϶����������, ͬʱ����X����NodeType
						// ע��value �� variable ���� true
						// ���ڶ�Ӧ�� chartoNode
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

				// ������ջ
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
	 * �˴������ؿ�ָ�룬�ڸ�ֵ����л��ж��Ƿ�Ϊ��ָ�룬���Ϊ�գ����
	 * ��Block���½�ָ������Map�������Ϊ�գ���ֱ���޸Ĵ洢�ڴ˴���ָ�����
	 * ����new��delete�����½�����
	 */

	//####
	/*
	 * ���ڻ�����ʱָ������,����Node�м�¼ָ���������ʣ�
	 * ���Ϊ��ʱ����������
	 */
}
