#include <string>
#include <map>
#include <fstream>

using namespace std;

//####
class InputHelper {
public:
	static const int A = 'A';
	static const int Z = 'Z';
	static map<string, char> Map;
	static bool isUp(int c)
	{
		return ((c >= A) && (c <= Z)) || ((c >= A - 64) && (c <= Z - 64));
	}
	static void help_input() {
		ifstream fin;
		ofstream fout;
		int nextUp = 'A';
		int nextDown = 'a';
		fin.open("InputTest.txt");
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
				}
			}
			if (nextUp == char(1))
				system("pause");
			if (isUp(word[0]) && nextUp < 'A' && (nextUp != char(1)))
				fout << char(Map[word] + 64) << '\'';
			if (nextUp == char(1))
				system("pause");
			else
				fout << Map[word];
		}
		fin.close();
		fout.close();
	}
};

map<string, char> InputHelper::Map;