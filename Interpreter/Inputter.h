#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Sentence.h"

using std::string;
using std::ifstream;

typedef std::vector<Sentence*> SenVector;

/**
 * \brief 
 * 用于读入预测分析表，预测分析表存储于InputTable.txt中，在未来对于其他语言拓展时，仅需要InputTable.txt文件即可
 */
class Inputter
{
	ifstream& fin_;
public:
	Inputter(ifstream& fin) :fin_(fin) { }
	~Inputter() = default;
	SenVector* get_sentence_vector() const;
};
