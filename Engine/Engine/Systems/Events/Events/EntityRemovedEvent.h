#pragma once

#include <Engine/Systems/Events/EventData.h>

class Entity;

class EntityRemovedEvent : public EventData {
public:
	Entity * entity;
	EntityRemovedEvent(Entity * e = nullptr) : entity(e) {}
};