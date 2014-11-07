#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Entity/Entity.h>

class EntityRemovedEvent : public EventData {
public:
	Entity * entity;
	EntityRemovedEvent(Entity * e = nullptr) : entity(e) {}
};