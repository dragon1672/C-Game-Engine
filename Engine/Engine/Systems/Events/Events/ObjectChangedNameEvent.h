#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Systems/Object.h>

class ObjectChangedNameEvent : public EventData {
public:
	Object * dude;
	std::string oldName;
	std::string newName;
	ObjectChangedNameEvent() : dude(nullptr) {}
	ObjectChangedNameEvent(Object * e, std::string o, std::string n) : dude(e), oldName(o), newName(n) {}
};