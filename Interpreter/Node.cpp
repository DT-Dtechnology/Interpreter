#include "Node.h"
#include "Object.h"
#include "stdafx.h"

#include <iostream>

Node::~Node() {
//	std::cout << "Value name:  " <<  value_->getName() << std::endl;
	
	if ( value_ != nullptr && value_->getName() == "" ) {
		delete value_;
	}
//	getchar();
}