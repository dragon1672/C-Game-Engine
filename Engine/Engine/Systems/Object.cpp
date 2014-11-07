#include "Object.h"
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ObjectChangedNameEvent.h>



int Object::GlobalID = 0;

Object::Object(std::string name) : id(GlobalID++), name(name)
{

}

std::string Object::Name() const
{
	return name;
}

void Object::Name(const std::string name)
{
	this->name = name;
}

int Object::getID() const
{
	return id;
}
