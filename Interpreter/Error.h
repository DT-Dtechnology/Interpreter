#pragma once
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

/**
 * \brief 
 * ����ʵ�ֱ������
 * ����ݴ������������ͬ����Ϣ
 */
class Error
{
	string message_;
public:
	Error(string message = "Unkown Error!") :message_(message)
	{
		cout << message << endl;
	}
	virtual ~Error() = default;
};

