#pragmaonce
#include<iostream>
#include<string>

usingstd::string;
usingstd::cout;
usingstd::endl;

classError
{
	stringmessage_;
public:
	Error(stringmessage="UnkownError!"):message_(message)
	{
		cout<<message<<endl;
	}
	virtual~Error()=default;
};

