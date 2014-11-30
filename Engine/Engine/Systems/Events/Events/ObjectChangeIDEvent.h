#pragma once

#include <Engine/Systems/Events/EventData.h>

class Object;

class ObjectChangeIDEvent : public EventData {
public:
	Object * o;
	double old,n;
	bool fromCereal;
	ObjectChangeIDEvent(Object * obj, double o, double n, bool fromCereal = false) : o(obj), old(o), n(n), fromCereal(fromCereal) {}
};