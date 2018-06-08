#pragmaonce
#include<string>
#include<vector>
#include<fstream>
#include"Sentence.h"

usingstd::string;
usingstd::ifstream;

typedefstd::vector<Sentence*>SenVector;

classInputter
{
	ifstream&fin_;
public:
	Inputter(ifstream&fin):fin_(fin){}
	~Inputter()=default;
	SenVector*get_sentence_vector()const;
};
