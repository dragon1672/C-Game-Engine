#include "Object.h"




int Object::GlobalID = 0;

Object::Object() : id(GlobalID++), name(nullptr)
{

}

const char * Object::Name() const
{
	return name;
}

void Object::Name(const char * name)
{
	this->name = name;
}

int Object::getID() const
{
	return id;
}
