#include"stdafx.h"
#include"Object.h"


LongObject*LongObject::operator+(constLongObject*longobj)const
{
	returnnewLongObject(this->value_+longobj->value_);
}

LongObject*LongObject::operator-(constLongObject*longobj)const
{
	returnnewLongObject(this->value_-longobj->value_);
}

LongObject*LongObject::operator*(constLongObject*longobj)const
{
	returnnewLongObject(this->value_*longobj->value_);
}

DoubleObject*LongObject::operator/(constLongObject*longobj)const
{
	returnnewDoubleObject(this->value_/longobj->value_);
}