#pragmaonce
#include"Object.h"
classObjectFactory
{
public:
	ObjectFactory()=default;
	~ObjectFactory()=default;
	staticObject*createObject(conststring&name);
};

