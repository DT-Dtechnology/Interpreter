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
	string name_;
	SenVector s_v_;
	ifstream fin_;
public:
	Inputter(const string& name);
	~Inputter() = default;
	void transfer();
	SenVector& get_sentence_vector() { return s_v_; }
};
