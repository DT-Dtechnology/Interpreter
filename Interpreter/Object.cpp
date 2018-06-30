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
	throw Error("unprovoked call");
	system("pause");
	return nullptr;
}
Object* Object::multiply(Object* obj)
{
	throw Error("unprovoked call");
}
Object* Object::divide(Object* obj)
{
	throw Error("unprovoked call");
}

Object * Object::more_or_equal(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::more(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::less_or_equal(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::less(Object *obj) {
	throw Error("unprovoked call");
}

Object * Object::equal(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::not_equal(Object *obj) {
	throw Error("unprovoked call");
}

Object * Object::leftmove(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::rightmove(Object *obj) {
	throw Error("unprovoked call");
}

Object * Object::mod(Object *obj) {
	throw Error("unprovoked call");
}

Object * Object::And(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::Or(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::Not() {
	throw Error("unprovoked call");
}

Object * Object::ByteAnd(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::ByteOr(Object *obj) {
	throw Error("unprovoked call");
}
Object * Object::Xor(Object *obj) {
	throw Error("unprovoked call");
}

Object * Object::negative() {
	throw Error("unprovoked call");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
	}
}
Object * LongObject::divide(Object *right) {
	double rval = right->get_val();
	double res = this->get_val() / rval;
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		return new DoubleObject(res);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}

Object * DoubleObject::add(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() + rval;
		return new DoubleObject(res);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}
Object * DoubleObject::minus(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() - rval;
		return new DoubleObject(res);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}
Object * DoubleObject::multiply(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double res = this->get_val() * rval;
		return new DoubleObject(res);
	}
	else {
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
	}
}

Object * StringObject::add(Object * right) {
	const ObjectType rtype = right->getType();
	
	if (rtype == StringObj) {
		StringObject *new_rgt = dynamic_cast<StringObject *>(right);
		string l = this->get_val();
		string r = new_rgt->get_val();
		string res = "\'";
		if (!(l[0] == '\'' && l[l.length() - 1] == '\'') || (l[0] == '\"' && l[l.length() - 1] == '\"')) {
			if (!((r[0] == '\'' && r[r.length() - 1] == '\'') || (r[0] == '\"' && r[r.length() - 1] == '\"'))) {
				throw Error("quotation mark missing ");
			}
		}
		for( int i=1; i<l.length()-1; ++i){
			res += l[i];
		}
		for (int i = 1; i < r.length() - 1; ++i) {
			res += r[i];
		}
		res += '\'';
		return new StringObject(res);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}

Object * LongObject::more_or_equal(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval >= rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}
Object * LongObject::more(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval > rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}
Object * LongObject::less_or_equal(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval <= rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}
Object * LongObject::less(Object * right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval < rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::leftmove(Object *right) {
	if (right->getType() == LongObj || right->getType() == DoubleObj) {
		long rval = right->get_val();
		long curval = this->get_val();
		return new LongObject(curval << rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::rightmove(Object *right) {
	if (right->getType() == LongObj || right->getType() == DoubleObj) {
		long rval = right->get_val();
		long curval = this->get_val();
		return new LongObject(curval >> rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::mod(Object *right) {
	if (right->getType() == LongObj || right->getType() == DoubleObj){
		long rval = right->get_val();
		return new LongObject(this->get_val() % rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}

	string line = this->get_val();
	string res = "";
	bool correct = true;
	int i = 0;
	int cnt = 0; 
	int size = num_vect.end() - num_vect.begin();

	if ( (line[0] == '\"' && line[line.length()-1] == '\"') || (line[0] == '\'' && line[line.length()-1] == '\'') ) {
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
		throw Error("quotation mark missing OR mismatch");
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
		throw Error("TypeError: unsupported operand types");
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
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * BoolObject::Not() {
	return new BoolObject( !(this->get_val()) );
	
}

Object * LongObject::equal(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval == rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * LongObject::not_equal(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval != rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}


Object * DoubleObject::equal(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval == rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * DoubleObject::not_equal(Object *right) {
	if ((right->getType() == LongObj) || (right->getType() == DoubleObj)) {
		double rval = right->get_val();
		double curval = this->get_val();
		return new BoolObject(curval != rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * StringObject::equal(Object *right) {
	if (right->getType() == StringObj) {
		StringObject *new_rgt = dynamic_cast<StringObject *>(right);
		string r = new_rgt->get_val();
		string l = this->get_val();
		return new BoolObject(l == r);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * StringObject::not_equal(Object *right) {
	if (right->getType() == StringObj) {
		StringObject *new_rgt = dynamic_cast<StringObject *>(right);
		string r = new_rgt->get_val();
		string l = this->get_val();
		return new BoolObject(l != r);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * BoolObject::equal(Object *right) {
	if (right->getType() == BoolObj) {
		BoolObject *new_rgt = dynamic_cast<BoolObject *>(right);
		bool r = new_rgt->get_val();
		bool l = this->get_val();
		return new BoolObject(l == r);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}
Object * BoolObject::not_equal(Object *right) {
	if (right->getType() == BoolObj) {
		BoolObject *new_rgt = dynamic_cast<BoolObject *>(right);
		bool r = new_rgt->get_val();
		bool l = this->get_val();
		return new BoolObject(l != r);
	}
	else {
		throw Error("TypeError: unsupported operand types");
		system("pause");
		return nullptr;
	}
}

Object * LongObject::negative() {
	return new LongObject(-this->get_val());
}
Object * DoubleObject::negative() {
	return new DoubleObject(-this->get_val());
}

void ListObject::append(Object* obj)
{
	value_.push_back(obj);
}

Object * DoubleObject::leftmove(Object *right) {
	if (right->getType() == LongObj || right->getType() == DoubleObj) {
		long rval = right->get_val();
		long curval = this->get_val();
		return new LongObject(curval << rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}

Object* DoubleObject::mod(Object* obj)
{
	if (obj->getType() == LongObj || obj->getType() == DoubleObj) {
		long rval = obj->get_val();
		return new LongObject(long(this->get_val()) % rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}

Object * DoubleObject::rightmove(Object *right) {
	if (right->getType() == LongObj || right->getType() == DoubleObj) {
		long rval = right->get_val();
		long curval = this->get_val();
		return new LongObject(curval >> rval);
	}
	else {
		throw Error("TypeError: unsupported operand types");
	}
}
