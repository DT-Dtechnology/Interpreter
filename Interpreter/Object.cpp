#include "stdafx.h"
#include "Object.h"

/*
LongObject* operator+(const LongObject* longobj);
LongObject* operator-(const LongObject* longobj);
LongObject* operator*(const LongObject* longobj);
DoubleObject* operator/(const LongObject* longobj);
*/

LongObject * LongObject::operator+(const LongObject *longobj) {
	return new LongObject(this->value_ + longobj->value_);
}

LongObject * LongObject::operator-(const LongObject *longobj) {
	return new LongObject(this->value_ - longobj->value_);
}

LongObject * LongObject::operator*(const LongObject *longobj) {
	return new LongObject(this->value_ * longobj->value_);
}

DoubleObject * LongObject::operator/(const LongObject *longobj) {
	return new DoubleObject(this->value_ / longobj->value_);
}