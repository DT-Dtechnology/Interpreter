#pragma once
#include <string>
#include <vector>
#include <queue>
#include "Word.h"
#include "Object.h"

using std::string;
using std::vector;
using std::queue;

typedef queue<Word> WordQueue;

class SenDivider
{
	string command;
	Block* cur_block;
public:
	SenDivider(const string& order) :command(order) {}
	~SenDivider() = default;
	WordQueue* work();
	//####
};
