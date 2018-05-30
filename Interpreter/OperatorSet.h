#pragma once
#include <set>
#include <string>

using std::set;
using std::string;

string python_operator[] =
{
	"+", "-", "*", "/", "%", "&", "|", "=",
	"**", "^", "~", "//", "[", "]", ":",
	"<<", ">>", "<=", "==", "!=", ">=",
	"<", ">", "%=", "<>", "/=","-=",
	"+=", "*=", "++", "(", ")", ",", "--"
};

set<string> operatorSet(python_operator, python_operator + sizeof(python_operator) / sizeof(string *));


string _keyword[] =
{ "False",  "def",      "if",     "raise",  "None",    "del",   "import",
"return",  "True",     "elif",   "in",     "try",     "and",   "else",
"is",      "while",    "as",     "except", "lambda",  "with",  "assert",
"finally", "nonlocal", "yield",  "break",  "for",     "class", "from",
"or",      "continue", "global", "pass", "not"
};

/*
*"False",  "def",      "if",   "None",
*"return",  "True",     "elif",   "in",    "and",   "else",
*"is",  "while",
*"break",  "for", "from",
*"or",      "continue", "pass", "not"£¬ "break"
*
*/

set<string> KeyWordSet(_keyword, _keyword + sizeof(_keyword) / sizeof(string *));