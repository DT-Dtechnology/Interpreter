#include "stdafx.h"
#include "Object.h"


LongObject * LongObject::operator+(const LongObject *longobj) const
{
	return new LongObject(this->value_ + longobj->value_);
}

LongObject * LongObject::operator-(const LongObject *longobj) const
{
	return new LongObject(this->value_ - longobj->value_);
}

LongObject * LongObject::operator*(const LongObject *longobj) const
{
	return new LongObject(this->value_ * longobj->value_);
}

DoubleObject * LongObject::operator/(const LongObject *longobj) const
{
	return new DoubleObject(this->value_ / longobj->value_);
}