#pragma once
#include <set>
#include <string>

using std::set;
using std::string;

/*
 * 用于记录全部的关键字和运算符
 */


string python_operator[] =
{
	"+", "-", "*", "/", "%", "&", "|", "=",
	"**", "^", "~", "//", "[", "]",
	"<<", ">>", "<=", "==", "!=", ">=",
	"<", ">", "%=", "<>", "/=","-=",
	"+=", "*=", ",", "(", ")"
};

set<string> operatorSet(python_operator, python_operator + 31);


string python_keyword[] =
{"def",      "if",     "raise",  "None",    "del",   "import",
"return",  "elif",   "in",     "try",     "and",   "else",
"is",      "while",    "as",     "except", "lambda",  "with",  "assert",
"finally", "nonlocal", "yield",  "break",  "for",     "class", "from",
"or",      "continue", "global", "pass", "not", "print", ":"
};



set<string> KeyWordSet(python_keyword, python_keyword + 33);