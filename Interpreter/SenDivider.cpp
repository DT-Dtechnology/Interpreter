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

WordQueue* SenDivider::work()
{
	//####
	cout << endl << endl << "----------" << endl << "Divider: " << endl << command << endl << "---------" << endl << endl;

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
	return word_list;
}
