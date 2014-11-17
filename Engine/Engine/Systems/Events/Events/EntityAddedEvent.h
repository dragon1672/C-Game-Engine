#pragma once

#include <Engine/Systems/Events/EventData.h>

class Entity;

class EntityAddedEvent : public EventData {
public:
	Entity * entity;
	EntityAddedEvent(Entity * e = nullptr) : entity(e) {}
};