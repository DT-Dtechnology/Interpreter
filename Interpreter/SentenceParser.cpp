#include "stdafx.h"
#include "SentenceParser.h"
#include "Object.h"
#include "Error.h"
#include "Matrix.h"
#include "SenDivider.h"
#include "Traveller.h"

using std::queue;
using std::stack;
using std::cout;
using std::endl;

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
	auto X = ParseStack.top();
	while (FLAG)
	{
		X = ParseStack.top();
		ParseStack.pop();
		NodeType Top = X->getNodeType();

		if (Top == NodeType::TERMINATE)
		{
			// cout << front << "  ";
			if (X->value_->getType() == ObjectType::Operator && front!= "#")
			{
				// isTerminate[] 表示终结符
				// stringToChar[] 表示终结符的转化
				const int tmp = stringToChar[front];
				// 终结符转NodeType 例如：+->ADD
				X->nodeType_ = charToNode[tmp];
				word_queue_.pop();
				front = getNodeMsg(word_queue_.front());
			}
			else if(X->value_->getType() == ObjectType::Operator)
			{
				// front == "#";
				const int tmp = stringToChar[front];
				// 终结符转NodeType 例如：+->ADD
				X->nodeType_ = charToNode[tmp];
			}
			else if (X->getValue()->getType() == ObjectType::TotalVariable)
			{
				// X 更新 Object 所指向的内容
				//释放管理，在Varieble对应的Node上，isTemp为false，默认为true
				//用于表示不能删除
				ObjectType type = X->getValue()->getType();
				X->value_ = getObject(cur_block_, word_queue_.front().getMsg());
				word_queue_.pop();
				front = getNodeMsg(word_queue_.front());
			}
			else
				throw Error("Syntax Error");
		}
		else if (Top == NodeType::END)
		{
			if (front == "#")
				FLAG = false;
			else
				throw Error("Syntax Error");
		}
		else if (Matrix[nodeToInt[Top]][stringToInt[front]] != "_")
		{
			//nodeToInt 行号
			//stringToInt 列好
			string magic_code = Matrix[nodeToInt[Top]][stringToInt[front]];

			// 顺序生成X的子节点
			for (auto i = 0; i < magic_code.length(); ++i)
			{
				if (magic_code[i] == '~')
					continue;
				if (isUnTerminate[magic_code[i]])
				{
					const NodeType type = charToNode[magic_code[i]];
					Node* node = new Node(type);
					node->parent_ = X;
					X->addNode(node);
				}
				else if (isTerminate[magic_code[i]])
				{
					// 判断读入符号类型, 同时处理X结点的NodeType
					// 注意value 和 variable 不是 true
					// 基于对应的 chartoNode
					Node* node = new Node(TERMINATE);
					node->setValue(new OperatorObject());
					node->parent_ = X;
					node->isLeaf_ = true;
					X->addNode(node);
				}
				else
				{
					Node* node = new Node(NodeType::TERMINATE);
					node->setValue(new VariableObject());
					node->isLeaf_ = true;
					node->parent_ = X;
					X->addNode(node);
				}
			}

			// 倒序入栈
			for (auto it = X->childVector_.end(); it != X->childVector_.begin();)
				ParseStack.push(*(--it));
		}
		else
			throw Error("Syntax Error");
		
	}
	root_ = Root;
}

void SentenceParser::prepareNode(Node* node)
{
	auto it = node->childVector_.begin();
	while (it != node->childVector_.end())
	{
		Node* tmp = *it;
		if (tmp->getNodeType() == TERMINATE || isOperator[tmp->nodeType_])
			;
		else if(tmp->childVector_.size() == 0)
		{
			it = node->childVector_.erase(it);
			continue;
		}
		else
			prepareNode(*it);
		++it;
	}
}

ControlStatus SentenceParser::getStatus() const
{
	if( root_->getNodeType() == IF )
	{
		BoolObject *temp = dynamic_cast<BoolObject*>(root_->getValue());
		bool val = temp->get_val();
		if(val)
		{
			
			return IFTRUE;
		}else
		{
			
			return IFFALSE;
		}
	}
	if (root_->getNodeType() == LOOP)
	{
		BoolObject *temp = dynamic_cast<BoolObject*>(root_->getValue());
		const bool val = temp->get_val();
		if (val)
		{
			
			return LOOPTRUE;
		}
		else
		{
			
			return LOOPFALSE;
		}
	}
	if(root_->getNodeType() == DEF)
	{
		return DEFSTA;
	}
	if(root_->getNodeType() == RETURN)
	{
		return RETURNSTA;
	}
	return USELESS;
}

ControlStatus SentenceParser::work()
{
	divide();
	buildTree();
	prepareRoot();

	upFloat();
	
	parserRoot();
	return getStatus();
}

void SentenceParser::upFloat()
{
	// bfs
	queue<Node*> nodeQueue;
	queue<Node*> upQueue;
	nodeQueue.push(root_);
	Node *node;
	while (!nodeQueue.empty()) 
	{
		node = nodeQueue.front();
		nodeQueue.pop();
		if (doubleOperator[node->getNodeType()])
		{
			upQueue.push(node);
		}
		if (node->getChild()->size() > 0)
		{
			for (auto it = node->getChild()->begin(); it != node->getChild()->end(); it++)
				nodeQueue.push(*it);
		}
	}

	// float
	while (!upQueue.empty())
	{
		node = upQueue.front();
		upQueue.pop();
		node->getParent()->getParent()->setNodeType(node->getNodeType());
		auto it = node->getParent()->getChild()->begin();
		while (it != node->getParent()->getChild()->end())
		{
			if (*it == node)
			{
				it = node->getParent()->getChild()->erase(it);
				break;
			}
			++it;
		}
	}

	// comma
	nodeQueue.push(root_);
	while (!nodeQueue.empty())
	{
		node = nodeQueue.front();
		bool flag = 0;
		if (node->getNodeType() == LISTFLAG)
		{
			auto it1 = node->getChild()->begin();
			while (it1 != node->getChild()->end())
			{
				if ((*it1)->getNodeType() == LISTFLAG)
				{
					NodeVector temp;
					auto it2 = (*it1)->getChild()->begin();
					while (it2 != (*it1)->getChild()->end())
					{
						temp.push_back(*it2);
						++it2;
					}
					it1 = node->getChild()->erase(it1);
					for (auto it = temp.begin(); it != temp.end(); it++)
						node->addNode(*it);
					flag = 1;
					node->setNodeType(LISTFLAG);
					break;
				}
				++it1;
			}
		}
		if (flag == 0)
		{
			nodeQueue.pop();
			if (node->getChild()->size() > 0)
			{
				for (auto it = node->getChild()->begin(); it != node->getChild()->end(); it++)
					nodeQueue.push(*it);
			}
		}
	}

	//func, +/-, elif
	
	nodeQueue.push(root_);
	while (!nodeQueue.empty())
	{
		node = nodeQueue.front();
		nodeQueue.pop();

		if (node->getChild()->size() > 0)
		{
			
			auto it = node->getChild()->begin();
			while (it != node->getChild()->end())
			{
				if ((*it)->getNodeType() == FUNC)
				{

					Node* temp = *(it - 1);
					(*it)->getChild()->insert((*it)->getChild()->begin(), temp);
					it = node->getChild()->erase(it - 1);
					break;
				}
				++it;
			}
		}
		
		if (node->getChild()->size() == 1 && (node->getNodeType() == ADD || node->getNodeType() == MINUS))
		{
			if (node->getNodeType() == ADD)
				node->setNodeType(POSI);
			else
				node->setNodeType(NEGA);
		}
		
		if(node->getNodeType() == IF)
		{
			if (node->childVector_[0]->getNodeType() == ELIF)
				node->nodeType_ = ELIF;
		}

		if (node->getNodeType() == LOOP)
		{
			if (node->childVector_[0]->getNodeType() == FOR)
				node->nodeType_ = FOR;
			if (node->childVector_[0]->getNodeType() == WHILE)
				node->nodeType_ = WHILE;
		}

		if (node->getNodeType() == JUMP)
		{
			if (node->childVector_[0]->getNodeType() == RETURN)
				node->nodeType_ = RETURN;
			if (node->childVector_[0]->getNodeType() == BREAK)
				node->nodeType_ = BREAK;
			if (node->childVector_[0]->getNodeType() == CONTINUE)
				node->nodeType_ = CONTINUE;
		}

		if (node->getChild()->size() > 0)
		{
			for (auto it = node->getChild()->begin(); it != node->getChild()->end(); it++)
				nodeQueue.push(*it);
		}
	}
	
	// def
	if  (root_->getChild()->size() == 1 && (*root_->getChild()->begin())->getNodeType() == DEF)
	{
		Node* temp = *root_->getChild()->begin();
		while (temp->getNodeType() != FUNC)
		{
			temp->setNodeType(SEN);
			temp = *temp->getChild()->begin();
		}
		temp->setNodeType(DEF);
	}
}

void SentenceParser::build_all()
{
	buildAll();
	//printMatrix();
}

Object* getObject(Block* cur_block, string name)
{
	// ####
	return new TempObject(name);

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
