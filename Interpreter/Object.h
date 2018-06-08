#pragmaonce
#include<iostream>
#include<vector>

usingstd::string;
usingstd::vector;

enumObjectType
{
	DEBUG_TEST,TotalVariable,TotalValue,Operator,LongObj,
	DoubleObj,StringObj,TupleObj,ListObj,DictObj,
	BoolObj
};

classObject
{
	ObjectTypetype_;
	boolisTemp_=false;
public:
	Object(ObjectTypetype):type_(type){}
	virtual~Object()=default;
	ObjectTypegetType()const{returntype_;}
	voidsetTemp(){isTemp_=true;}
	boolgetStatus()const{returnisTemp_;}
};

classValueObject:
	publicObject
{
public:
	ValueObject():Object(ObjectType::TotalValue){}
	~ValueObject()override=default;
};

classVariableObject:
	publicObject
{
public:
	VariableObject():Object(ObjectType::TotalVariable){}
	~VariableObject()override=default;
};

classOperatorObject:
	publicObject
{
public:
	OperatorObject():Object(ObjectType::Operator){}
	~OperatorObject()override=default;
};

classTestObject:
	publicObject
{
	std::stringvar_name_;
public:
	TestObject(conststd::string&var_name)
		:Object(ObjectType::DEBUG_TEST)
	{
		var_name_=var_name;
	}
	~TestObject()=default;
	voidprint_test()const
	{
		std::cout<<var_name_<<"";
	}
};

classLongObject;
classDoubleObject;
classStringObject;
classBoolObject;
classTupleObject;
classListObject;
classDictObject;

classLongObject:
	publicObject
{
	longvalue_;
public:
	LongObject(constlong&_val):Object(ObjectType::LongObj),value_(_val){}
	~LongObject()=default;
	LongObject*operator+(constLongObject*longobj)const;
	LongObject*operator-(constLongObject*longobj)const;
	LongObject*operator*(constLongObject*longobj)const;
	DoubleObject*operator/(constLongObject*longobj)const;

	//
};


classDoubleObject:publicObject{
	doublevalue_;
public:
	DoubleObject(constdouble&_val):Object(ObjectType::DoubleObj),value_(_val){}
	~DoubleObject()=default;

};

classStringObject:publicObject
{
	stringvalue_;
public:
	StringObject(conststring&_val):Object(ObjectType::StringObj),value_(_val){}
	~StringObject()=default;

};

classBoolObject:publicObject
{
	boolvalue_;
public:
	BoolObject(boolvalue):Object(BoolObj),value_(value){}
	~BoolObject()=default;
};

classListObject:publicObject
{
	vector<Object*>value_{};
public:
	ListObject():Object(ObjectType::ListObj){}
	~ListObject()=default;

};