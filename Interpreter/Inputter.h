#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "SentenceVector.h"

using std::string;
using std::ifstream;

class Inputter
{
	string name_;
	SentenceVector s_v_;
	ifstream fin_;
public:
	Inputter(const string& name);
	~Inputter() = default;
	void transfer();
	SentenceVector& get_sentence_vector() { return s_v_; }
};

