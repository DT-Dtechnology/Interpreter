#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Sentence.h"

using std::string;
using std::ifstream;

typedef std::vector<Sentence*> SenVector;

class Inputter
{
	ifstream& fin_;
public:
	Inputter(ifstream& fin) :fin_(fin) { }
	~Inputter() = default;
	SenVector* get_sentence_vector() const;
};
