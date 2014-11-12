#include "Object.h"
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ObjectChangedNameEvent.h>
#include <Engine/IO/Stream.h>

namespace {
	union GUIDBinder {
		GUID guid;
		double myDouble;
	};
}

Object::Object(std::string name) : name(name)
{
	CoCreateGuid(&id);
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
		emitEvent(data);
	}
}

double Object::getID() const
{
	return GUID2Double(id);
}

std::string Object::GUID2string(const GUID& guid)
{
	char buff[38];
	sprintf_s(buff, "{%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}",
		guid.Data1, guid.Data2, guid.Data3, 
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	std::string buffAsStdStr = buff;
	return buffAsStdStr;
}

GUID Object::double2GIUD(const double d)
{
	GUIDBinder bind;
	bind.myDouble = d;
	return bind.guid;
}

double Object::GUID2Double(const GUID& guid)
{
	GUIDBinder bind;
	bind.guid = guid;
	return bind.myDouble;
}

void Object::Save(Stream& os)
{
	os << id << name;
}

void Object::Load(Stream& os)
{
	os >> id >> name;
}
