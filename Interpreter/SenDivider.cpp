#include "stdafx.h"
#include "SenDivider.h"
#include <queue>
#include "Word.h"
#include "OperatorSet.h"
#include "TypeDetecter.h"

inline bool isChar(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z' || c == '_');
}

inline bool isNum(char c)
{
	return c >= '0' && c <= '9';
}

inline bool dotDetect(string& s, int pos)
{
	if (pos != s.length() - 1 && pos != 0)
		return !(isChar(s[pos - 1]) && isChar(s[pos + 1]));
	else if (pos == 0)
		return isNum(s[0]);
	else
		return isNum(s[s.length() - 2]);
}

inline bool minusDetect(string& s, int pos)
{
	if (pos == 0)
		return true;
	else
		return isNum(s[pos - 1]);
}

inline bool isElse(char c)
{
	return !(isChar(c) || isNum(c));
}

inline bool findOperater(string& s, int& pos)
{
	if (pos == s.length() - 1)
		return (operatorSet.find(s.substr(pos, 1)) != operatorSet.end());
	bool match_one = (operatorSet.find(s.substr(pos, 1)) != operatorSet.end());
	bool match_two = (operatorSet.find(s.substr(pos, 2)) != operatorSet.end());
	if (match_two)
	{
		pos += 1;
		return true;
	}
	else if (match_one)
	{
		pos += 0;
		return true;
	}
	else
		return false;
}

inline string spaceKiller(const string& s)
{
	string temp_str;
	for (auto i = 0; i < s.length(); ++i)
		if (s[i] != ' ')
			temp_str += s[i];
	return temp_str;
}


typedef stack<Word> WordStack;

WordQueue* SenDivider::work()
{

	WordQueue* word_list = new WordQueue;
	int start_posi = 0;
	for (auto i = 0; i < command.length(); ++i)
	{
		const auto temp = i;
		string quoted = "";
		//detect quote "  
		if (command[i] == '\"') {

			while (command[++i] != '\"' && i < command.length()) {
				quoted += command[i];
			}
			if (i == command.length()) {
				system("pause");
				//不能处理已经进入队列的。
				exit(1);
			}
			++i;
			start_posi = i;
			string str = "\"" + quoted + "\"";
			word_list->push(Word(DetectType(str), str));
			continue;
		}
		//detect quote '
		if (command[i] == '\'') {
			while (command[++i] != '\'' && i < command.length()) {
				quoted += command[i];
			}
			if (i == command.length()) {
				system("pause");
				//不能处理已经进入队列的。
				exit(1);
			}
			++i;
			start_posi = i;
			string str = "\'" + quoted + "\'";
			word_list->push(Word(DetectType(str), str));
			continue;
		}

		if (command[i] == ' ' || command[i] == ':')
		{
			string str = spaceKiller(command.substr(start_posi, temp - start_posi));
			if (str.length() != 0)
				word_list->push(Word(DetectType(str), str));
			start_posi = i;
			continue;
		}
		if (findOperater(command, i))
		{
			string str = spaceKiller(command.substr(start_posi, temp - start_posi));
			if (str.length() != 0)
				word_list->push(Word(DetectType(str), str));
			str = spaceKiller(command.substr(temp, i + 1 - temp));
			if (str.length() != 0)
				word_list->push(Word(DetectType(str), str));
			start_posi = i + 1;
		}
	}
	string str = spaceKiller(command.substr(start_posi, command.length() - start_posi));
	if (str.length() != 0)
		word_list->push(Word(DetectType(str), str));

	WordQueue* new_word_list = new WordQueue;
	WordStack word_stack;
	WordStack tmp_stack;
	while(!word_list->empty())
	{
		if (word_list->front().getType() == WordType::word_type_error)
			throw Error("Word Type Error");
		if (word_list->front().getType() == WordType::keyword)
		{
			while (!word_stack.empty())
			{
				new_word_list->push(word_stack.top());
				word_stack.pop();
			}
			new_word_list->push(word_list->front());
			word_list->pop();
		}
		else if(word_list->front().getType() == WordType::value 
			|| word_list->front().getType() == WordType::variable)
		{
			if (!tmp_stack.empty())
			{
				word_stack.push(Word(WordType::operate, "\'"));
				word_stack.push(word_list->front());
				if (!tmp_stack.empty())
				{
					word_stack.push(tmp_stack.top());
					tmp_stack.pop();
				}
				word_stack.push(Word(WordType::operate, "\""));
				word_list->pop();
			}
			else
			{
				word_stack.push(word_list->front());
				word_list->pop();
			}
		}
		else if(word_list->front().getMsg() == "+" 
			|| word_list->front().getMsg() == "-" 
			|| word_list->front().getMsg() == "not")
		{
			if(!word_stack.empty() && (word_stack.top().getType() != operate 
				|| word_stack.top().getMsg() == "\'"
				|| word_stack.top().getMsg() == "\""
				|| word_stack.top().getMsg() == ")"))
			{
				word_stack.push(word_list->front());
				word_list->pop();
			}
			else
			{
				tmp_stack.push(word_list->front());
				word_list->pop();
			}
		}
		else
		{
			word_stack.push(word_list->front());
			word_list->pop();
		}
	}
	while (!word_stack.empty())
	{
		new_word_list->push(word_stack.top());
		word_stack.pop();
	}
	

	while(!new_word_list->empty())
	{
		if (new_word_list->front().getMsg() == "(")
			word_list->push(Word(WordType::operate, ")"));
		else if (new_word_list->front().getMsg() == ")")
			word_list->push(Word(WordType::operate, "("));
		else if (new_word_list->front().getMsg() == "\'")
			word_list->push(Word(WordType::operate, ")"));
		else if (new_word_list->front().getMsg() == "\"")
			word_list->push(Word(WordType::operate, "("));
		else
			word_list->push(new_word_list->front());
		new_word_list->pop();
	}

	typedef vector<Word> WordVec;
	WordVec *tvt = new WordVec;
	while ( !word_list->empty()) {
		tvt->push_back(word_list->front());
		word_list->pop();
	}
	WordVec *nvt = new WordVec;
	queue<int> leftmark;
	queue<int> rightmark;
	WordQueue *func_name = new WordQueue;
	int cnt = 0;
	for (auto i = tvt->begin(); i != tvt->end(); ++i, ++cnt) {
		if (i->getMsg() == ")") {
			auto j = ++i;
			--i;
			if (j == tvt->end()) {
				break;
			}

			if (j->getType() == WordType::variable) {
				int num = 0;
				int temp = cnt;
				bool find = false;

				for (auto k = i; ; --temp) {
					
					if (k->getMsg() == ")") {
						--num;
					}
					else if (k->getMsg() == "(") {
						++num;
					}
					if (num == 0) {
						find = true;
						break;
					}
					if (k == tvt->begin()) {
						break;
					}
					--k;

				}

				if (find) {
					leftmark.push(temp);
					rightmark.push(cnt+1);
					func_name->push(*j);
				}
			}
		}
	}

	const int size = tvt->size();
	for (int i = 0; i < size; ++i) {
		if (!leftmark.empty() && i == leftmark.front()) {
			nvt->push_back(func_name->front());
			leftmark.pop();
			func_name->pop();
			nvt->push_back(tvt->operator[](i));
		}
		else if (!rightmark.empty() && i == rightmark.front()) {
			rightmark.pop();
		}
		else {
			nvt->push_back(tvt->operator[](i));
		}
	}

	WordQueue *nwl = new WordQueue;
	for (auto i : *nvt) {
		nwl->push(i);
	}

	
	delete tvt;
	delete func_name;
	delete new_word_list;
	delete word_list;
	return nwl;
}