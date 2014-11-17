#pragma once

#include <Engine/Systems/Events/EventData.h>

class Entity;
class Component;

class ComponentAddedEvent : public EventData {
public:
	Entity * entity;
	Component * beingAdded;
	ComponentAddedEvent() : entity(nullptr), beingAdded(nullptr) {}
	ComponentAddedEvent(Entity * e, Component * c) : entity(e), beingAdded(c) {}
};