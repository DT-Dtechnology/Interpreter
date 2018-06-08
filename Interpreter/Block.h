#pragmaonce
#include<stack>
#include<map>
#include"Object.h"
#include"Traveller.h"

classBlock;

usingstd::stack;
usingstd::map;
usingstd::string;
usingstd::vector;

typedefvector<Sentence*>SenVector;
typedefmap<string,Object*>VarTable;
typedefmap<string,Block*>FuncTable;

classBlock
{
	SenVector*sentence_vector_;
	stack<Block*>block_space_stack_;
	stack<Block*>temp_space_stack_;
	VarTablevar_table_;
	FuncTablefunc_table_;
	Travellertraveller_;
	Object*return_pos_=nullptr;

	voidreturnSpace();
public:
	Block(SenVector*sen_vector):sentence_vector_(sen_vector),traveller_(this){}
	~Block()=default;
	
	Object*searchObject(stringvar_name);

	voidprint_all();
	voidprint_all_old();
};
