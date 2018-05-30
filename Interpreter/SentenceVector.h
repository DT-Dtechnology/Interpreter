#pragma once
#include "Sentence.h"
#include <vector>

using std::vector;

class SentenceVector
{
	vector<Sentence*> sentence_vector;
public:
	//All the operation is by using Iterator.
	SentenceVector() = default;
	~SentenceVector() = default;
	void push_back(Sentence* sentence) { sentence_vector.push_back(sentence); }
	//void insert(Sentence*, const int position);
	auto get_begin() { return sentence_vector.begin(); }
	auto get_end() { return sentence_vector.end(); }
	auto operator[](const int n) { return sentence_vector.begin() + n; }
	void printTest()
	{
		for (auto it = sentence_vector.begin(); it != sentence_vector.end(); ++it)
			(*it)->printTest();
	}
};

