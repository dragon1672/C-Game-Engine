#include "Object.h"




int Object::GlobalID = 0;

Object::Object() : id(GlobalID++), name(nullptr)
{

}

const char * Object::getName()
{
	return name;
}

int Object::getID()
{
	return id;
}
