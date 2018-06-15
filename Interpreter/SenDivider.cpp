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
	//####

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

		if (command[i] == ' ')
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
	
	/****
	while(!new_word_list->empty())
	{
		const Word tmp_word = new_word_list->front();
		new_word_list->pop();
		if(new_word_list->empty())
		{
			word_list->push(tmp_word);
			break;
		}
		Word new_tmp_word = Word();
		while(new_word_list->front().getMsg() == "not" 
			|| new_word_list->front().getMsg() == "-" 
			|| new_word_list->front().getMsg() == "+")
		{
			new_tmp_word = new_word_list->front();
			new_word_list->pop();
			if(new_word_list->empty())
			{
				while (!word_stack.empty())
				{
					word_list->push(word_stack.top());
					word_stack.pop();
				}
				word_list->push(new_tmp_word);
				new_tmp_word = Word();
				break;
				
			}
			if (new_word_list->front().getMsg() != "not" 
				&& new_word_list->front().getMsg() != "-" 
				&& new_word_list->front().getMsg() != "+")
			{
				while (!word_stack.empty())
				{
					word_list->push(word_stack.top());
					word_stack.pop();
				}
				break;
			}
			word_stack.push(new_tmp_word);
		}
		
		// ****

		word_list->push(tmp_word);
		if (new_tmp_word.getMsg() != "")
			word_list->push(new_tmp_word);
	}
	*/
	

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

	WordQueue *twl = new WordQueue;
	WordQueue *nwl = new WordQueue;
	while (!word_list->empty())
	{
		if (word_list->front().getMsg() == "(") {
			while (word_list->front().getMsg() != ")") {
				twl->push(word_list->front());
				word_list->pop();
			}
			twl->push(word_list->front());
			word_list->pop();

			if (word_list->empty()) {
				while (!twl->empty()) {
					nwl->push(twl->front());
					twl->pop();
				}
				break;
			}
			auto tar = word_list->front();
			if (tar.getType() == WordType::variable) {
				nwl->push(word_list->front());
				word_list->pop();
			}
			while (!twl->empty()) {
				nwl->push(twl->front());
				twl->pop();
			}
		}
		else {
			nwl->push(word_list->front());
			word_list->pop();
		}
			
	}
	delete new_word_list;
	delete twl;
	delete word_list;
	return nwl;
}