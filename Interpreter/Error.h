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
struct Error
{
	string message_;
	Error(string message = "Unkown Error!") :message_(message)
	{
		cout << "Error" << endl;
	}
	virtual ~Error() = default;
};

