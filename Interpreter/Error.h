#pragma once
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

/**
 * \brief 
 * 用于实现报错机制
 * 会根据错误类型输出不同的信息
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

