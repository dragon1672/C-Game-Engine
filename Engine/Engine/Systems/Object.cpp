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
	std::string old = this->name;
	this->name = name;
	if(old != this->name) {
		ObjectChangedNameEvent data(this,old,name);
		emitEvent(ObjectChangedNameEvent,data);
	}
}

int Object::getID() const
{
	return id;
}
