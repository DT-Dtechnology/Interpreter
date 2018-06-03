#pragma once
#include "Block.h"
#include "Inputter.h"

class PVM
{
	Block* Global_;

	void input();
	void run();
public:
	PVM();
	~PVM();
	void work()
	{
		input();
		run();
	}
};

