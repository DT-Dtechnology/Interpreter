#pragmaonce
#include<string>
#include<iostream>//

usingstd::string;

enumSentenceType
{
	SentenceLoop,SentenceIf,SentenceDef,SentenceReturn,SentenceExp
};

classSentence
{
	SentenceTypesenType_;
	stringorder_;
	inttab_cnt_;
	introw_;//
public:
	Sentence()=delete;
	Sentence(std::string&order,inttab,introw);
	~Sentence();
	stringgetOrder()const{returnorder_;}
	voidprintTest()const{std::cout<<row_<<""<<tab_cnt_<<""<<order_<<'\n';}
};

inlineSentence::Sentence(std::string&order,inttab,introw):
	order_(order),tab_cnt_(tab),row_(row)
{
	
}
