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

DoubleObject * LongObject::operator/(const LongObject *longobj) const
{
	return new DoubleObject(this->value_ / longobj->value_);
}

ListObject::~ListObject()
{
	for (auto it = value_.begin(); it != value_.end(); ++it)
	{
		if ((*it)->getStatus())
			delete *it;
	}
}
