#pragma once

#include <Engine/Systems/Events/EventData.h>

class Entity;
class Component;

class ComponentRemovedEvent : public EventData {
public:
	Entity * entity;
	Component * beingTrashed;
	ComponentRemovedEvent() : entity(nullptr), beingTrashed(nullptr) {}
	ComponentRemovedEvent(Entity * e, Component * c) : entity(e), beingTrashed(c) {}
};