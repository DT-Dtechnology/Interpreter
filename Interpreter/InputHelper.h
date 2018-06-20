#pragma once
#include <string>
#include <map>
#include <fstream>

using namespace std;

/**
 * \brief 
 * ���ڴ������ʽ���������⣬�����ں��ڹ�����չ��ʵ�ֶ��ڶ������ԵĽ���
 * ���Ͳ�ͬ�����Խ���Ҫ�޸���Դ�ļ��е�InputHelp.txt�ļ������޸�ʱҪע�����ʽ����LL1Ҫ��
 */
class InputHelper {
public:
	static const int A = 'A';
	static const int Z = 'Z';
	static map<string, char> Map;
	static bool isUp(char c)
	{
		return ((c >= A) && (c <= Z)) || ((c >= A - 64) && (c <= Z - 64));
	}
	static bool isRealUp(char c)
	{
		return (c >= A) && (c <= Z);
	}
	static void help_input() {
		ifstream fin;
		ofstream fout;
		int nextUp = 'A';
		int nextDown = 'a';
		fin.open("InputHelp.txt");
		fout.open("NewTable.txt");
		string word;
		while (true)
		{
			fin >> word;
			if (word == "END")
				return;
			if (word == ";") {
				fout << endl;
				continue;
			}
			else if(word == "~"){
				fout << "~";
				continue;
			}
			else if (word == "->") {
				fout << word;
				continue;
			}
			else if (Map[word] == 0) {
				if (isUp(word[0]))
				{
					Map[word] = nextUp;
					++nextUp;
					if (nextUp > 'Z')
						nextUp = 1;
				}
				else {
					Map[word] = nextDown;
					++nextDown;
					if (nextDown > 'z')
						nextDown = 33;
					if (nextDown == '\'')
						nextDown++;
					if (nextDown == '#')
						nextDown++;
				}
			}
			if (isUp(word[0]) && !isRealUp(char(Map[word])))
				fout << char(Map[word] + 64) << '\'';
			else
				fout << Map[word];
		}
		fin.close();
		fout.close();
	}
};

map<string, char> InputHelper::Map;