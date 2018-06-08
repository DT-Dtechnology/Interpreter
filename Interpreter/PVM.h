#pragmaonce
#include"Block.h"
#include"Inputter.h"

classPVM
{
	Block*Global_;
	stringfile_name_;

	voidinput();
	voidrun();
public:
	PVM(stringfile_name):file_name_(file_name){}
	~PVM()=default;
	voidwork()
	{
		input();
		run();
	}
	voidprint_test_first();
	voidprint_test_second();
};

inlinevoidPVM::input()
{
	ifstreamfin;
	fin.open(file_name_);
	Inputter*inputter=newInputter(fin);
	Global_=newBlock(inputter->get_sentence_vector());
	deleteinputter;
}

inlinevoidPVM::run()
{
	
}

inlinevoidPVM::print_test_first()
{
	input();
	std::cout<<"HelloWorld"<<std::endl<<std::endl;
	Global_->print_all();
}

inlinevoidPVM::print_test_second()
{
	input();
	std::cout<<"HelloWorld"<<std::endl<<std::endl;
	Global_->print_all_old();
}

