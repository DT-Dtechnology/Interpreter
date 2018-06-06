#pragma once
#include <fstream>
#include <string>
#include <map>

using namespace std;

class InputHelper {
public:
	static const int A = 'A';
	static const int Z = 'Z';
	static const string END_MESSAGE;
	static map<string, char> Map;
	static bool isUp(int c)
	{
		return ((c >= A) && (c <= Z)) || ((c >= A - 64) && (c <= Z - 64));
	}
	static void inputg() {
		ifstream fin;
		ofstream fout;
		int nextUp = 'A';
		int nextDown = 'a';
		fin.open("TableTest.txt");
		fout.open("NewTable.txt");
		string word;
		while (true)
		{
			fin >> word;
			if (word == END_MESSAGE)
				return;
			if (word == ";") {
				fout << endl;
				continue;
			}
			else if (word == "->") {
				fout << word;
				continue;
			}
			else if (Map[word] == 0) {
				if (isUp((int)word[0]))
				{
					Map[word] = nextUp;
					++nextUp;
					if (nextUp > 'Z')
						nextUp = 0;
				}
				else {
					Map[word] = nextDown;
					++nextDown;
					if (nextDown > 'z')
						nextDown = 33;
				}
			}
			if (isUp(word[0]) && nextUp < 'A')
				fout << Map[word] + 64 << '\'';
			else
				fout << Map[word];
		}
		fin.close();
		fout.close();
	}
};

string const InputHelper::END_MESSAGE = "END_OF_FILE";