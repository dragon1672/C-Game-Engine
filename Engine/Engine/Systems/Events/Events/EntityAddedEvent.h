#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Entity/Entity.h>

class EntityAddedEvent : public EventData {
public:
	Entity * entity;
	EntityAddedEvent(Entity * e = nullptr) : entity(e) {}
};