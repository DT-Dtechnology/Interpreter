#pragmaonce
#include<string>
#include<vector>
#include<queue>
#include"Word.h"

usingstd::string;
usingstd::vector;
usingstd::queue;

typedefqueue<Word>WordQueue;

classSenDivider
{
	stringcommand;
	Block*cur_block;
public:
	SenDivider(conststring&order):command(order){}
	~SenDivider()=default;
	WordQueue*work();
	//####
};
