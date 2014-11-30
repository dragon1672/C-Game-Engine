#pragma once

#include <Engine/Systems/Events/EventData.h>

#include <string>

class Object;

class ObjectChangedNameEvent : public EventData {
public:
	Object * dude;
	std::string oldName;
	std::string newName;
	bool fromCereal;
	ObjectChangedNameEvent() : dude(nullptr) {}
	ObjectChangedNameEvent(Object * e, std::string o, std::string n,bool fromCereal = false) : dude(e), oldName(o), newName(n), fromCereal(fromCereal) {}
};