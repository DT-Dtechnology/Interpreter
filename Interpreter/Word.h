#pragmaonce
#include<string>
#include"Object.h"

usingstd::string;

enumWordType
{
	value,variable,operate,
	keyword,word_type_error
};

classWord
{
	WordTypeword_type_;
	stringmsg_;
public:
	Word()=default;
	~Word()=default;
	Word(WordTypetype,stringstr):word_type_(type),msg_(str){}
	stringgetMsg()const{returnmsg_;}
	voidsetMsg(stringmsg){msg_=msg;}
	WordTypegetType()const{returnword_type_;}
};
