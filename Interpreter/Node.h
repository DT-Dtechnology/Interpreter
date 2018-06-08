#pragmaonce
#include<vector>
#include"Object.h"

classBlock;
classNode;

typedefstd::vector<Node*>NodeVector;

enumNodeType
{
	ROOT,END,TERMINATE,VALUE,VARIABLE,
	EXP,SEN,ASS,LOOP,EXPL,EXPLL,DEF,FUNC,DEFF,
	EE,T,TT,F,FF,G,GG,H,HH,K,X,
	VARL,VARLL,IF,JUMP,PRINT,PRINTT,
	EQUAL,LEFT_BRACKET,RIGHT_BRACKET,ADD,MINUS,MULTIPLY,DIVIDE,IS_EQUAL,IS_NOT_EQUAL,
	LEFT_MOVE,RIGHT_MOVE,WHILE,FOR,IN,COLON,COMMA,NOT,BANG,PLUS_PLUS,MINUS_MINUS,
	ELIF,ELSE,CONTINUE,BREAK,PASS,RETURN,PARAL,PARALL,PARA
};

classNode
{
	Object*value_=nullptr;
	Node*parent_=nullptr;
	NodeVectorchildVector_;
	boolisLeaf_=false;
	NodeTypenodeType_;
public:
	Node();
	~Node();
	Node(NodeTypenodeType):nodeType_(nodeType){}
	NodeTypegetNodeType()const{returnnodeType_;};
	NodeVector*getChild(){return&childVector_;}
	Object*getValue()const;
	voidaddNode(Node*node){childVector_.push_back(node);}
	voidsetValue(Object*object){value_=object;}
	Node*getParent()const{returnparent_;}

	friendclassSentenceParser;
	friendvoidprint_node(Node*);
	friendvoidFuncSwitcher(Block*,Node*);
};

inlineNode::~Node()
{
	for(autoit=childVector_.begin();it!=childVector_.end();++it)
		delete*it;
	deletevalue_;
}

inlineObject*Node::getValue()const
{
	//####
	returnvalue_;
}
