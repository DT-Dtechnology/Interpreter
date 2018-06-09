#include "stdafx.h"
#include "Object.h"

double Object::get_val() {
	ObjectType rtype = this->getType();
	if (rtype == LongObj) {
		LongObject *new_rgt = dynamic_cast<LongObject *>(this);
		return new_rgt->get_val();
	}
	else if (rtype == DoubleObj) {
		DoubleObject *new_rgt = dynamic_cast<DoubleObject *>(this);
		return new_rgt->get_val();
	}
}


Object* Object::add(Object* obj)
{
	cout << "I think you ......" << endl;
	system("pause");
	return nullptr;
}

Object* Object::minus(Object* obj)
{
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object* Object::multiply(Object* obj)
{
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object* Object::divide(Object* obj)
{
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}

Object * Object::more_or_equal(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::more(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::less_or_equal(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::less(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}

Object * Object::leftmove(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::rightmove(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}

Object * Object::mod(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}

Object * Object::And(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::Or(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::Not() {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}

Object * Object::ByteAnd(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::ByteOr(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}
Object * Object::Xor(Object *obj) {
	cout << "unprovoked call" << endl;
	system("pause");
	return nullptr;
}

Object* TestObject::add(Object* object)
{
	TestObject* newobject = dynamic_cast<TestObject*>(object);
	string add_name = " (EMPTY) ";
	if (object)
		add_name = newobject->getName();
	return new TestObject(var_name_ + add_name);
}


Object * LongObject::add(Object *right) {
	double rval = right->get_val();
	double res = this->get_val() + rval;
	if (right->getType() == LongObj) {
		return new LongObject(res);
	}else if (right->getType() == DoubleObj) {
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::minus(Object *right) {
	double rval = right->get_val();
	double res = this->get_val() - rval;
	if (right->getType() == LongObj) {
		return new LongObject(res);
	}
	else if (right->getType() == DoubleObj) {
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::multiply(Object *right) {
	double rval = right->get_val();
	double res = this->get_val() * rval;
	if (right->getType() == LongObj) {
		return new LongObject(res);
	}
	else if (right->getType() == DoubleObj) {
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::divide(Object *right) {
	double rval = right->get_val();
	double res = this->get_val() / rval;
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * DoubleObject::add(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() + rval;
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::minus(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() - rval;
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::multiply(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() * rval;
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::divide(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() / rval;
		return new DoubleObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * StringObject::add(Object * right) {
	ObjectType rtype = right->getType();
	
	if (rtype == StringObj) {
		StringObject *new_rgt = dynamic_cast<StringObject *>(right);
		string res = this->get_val() + new_rgt->get_val();
		return new StringObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::more_or_equal(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval >= rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::more(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval > rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::less_or_equal(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval <= rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::less(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval < rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::more_or_equal(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval >= rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::more(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval > rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::less_or_equal(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval <= rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::less(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval < rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::leftmove(Object *right) {
	if (right->getType() == LongObj) {
		long rval = right->get_val();
		long curval = this->get_val();
		return new LongObject(curval << rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::rightmove(Object *right) {
	if (right->getType() == LongObj) {
		long rval = right->get_val();
		long curval = this->get_val();
		return new LongObject(curval >> rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::ByteAnd(Object *right) {
	if (right->getType() == LongObj) {
		long rval = right->get_val();
		return new LongObject(this->get_val() & rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::ByteOr(Object *right) {
	if (right->getType() == LongObj) {
		long rval = right->get_val();
		return new LongObject(this->get_val() | rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::Xor(Object *right) {
	if (right->getType() == LongObj) {
		long rval = right->get_val();
		return new LongObject(this->get_val() ^ rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::mod(Object *right) {
	if (right->getType() == LongObj){
		long rval = right->get_val();
		return new LongObject(this->get_val() % rval);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * StringObject::mod(Object *right) {
	vector<long> num_vect;
	if ( (right->getType() == LongObj) || (right->getType() == DoubleObj) ) {
		long num = right->get_val();
		num_vect.push_back(num);
	}
	else if (right->getType() == ListObj) {
		ListObject * new_rgt = dynamic_cast<ListObject *>(right);
		vector<Object *> * temp_vect = new_rgt->get_val();
		for (auto i : *temp_vect) {
			long temp = i->get_val();
			num_vect.push_back(temp);
		}
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}

	//for test
	cout << "----------" << endl;
	for (auto i : num_vect) {
		cout << i << endl;
	}
	cout << "----------" << endl;
	//end

	string line = this->get_val();
	string res = "";
	bool correct = true;
	int i = 0;
	int cnt = 0; 
	int size = num_vect.end() - num_vect.begin();

	cout << line[0] << "  " << line[line.length()-1] << endl;

	if ( (line[0] == '\"' && line[line.length()-1] == '\"') || (line[0] == '\'' && line[line.length()-1] == '\'') ) {
		cout << 'r' << endl;
		res += '\'';
		for (i = 1; i < line.length()-1; ++i) {
			if (line[i] == '%' && line[i + 1] == 'd') {
				if (cnt >= size) {
					correct = false;
					break;
				}
				res += std::to_string(num_vect[cnt++]);
				++i;
			}
			else {
				res += line[i];
			}
		}
		res += '\'';
		if (cnt != size) {
			correct = false;
		}
		else {
			return new StringObject(res);
		}
	}
	else {
		correct = false;
	}
	if (!correct) {
		Error("quotation mark missing OR mismatch");
		system("pause");
		return nullptr;
	}
}

Object * BoolObject::And(Object *right) {
	if (right->getType() == BoolObj) {
		BoolObject *new_rgt = dynamic_cast<BoolObject *>(right);
		bool l = this->get_val();
		bool r = new_rgt->get_val();
		bool res = l && r;
		return new BoolObject( res );
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * BoolObject::Or(Object *right) {
	if (right->getType() == BoolObj) {
		BoolObject *new_rgt = dynamic_cast<BoolObject *>(right);
		bool l = this->get_val();
		bool r = new_rgt->get_val();
		bool res = l || r;
		return new BoolObject(res);
	}
	else {
		Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * BoolObject::Not() {
	return new BoolObject( !(this->get_val()) );
	
}

void ListObject::append(Object* obj)
{
	value_.push_back(obj);
}
