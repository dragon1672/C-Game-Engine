#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Entity/Component.h>

class EntityParentChangedEvent : public EventData {
public:
	Entity * entity;
	Entity * newParent;
	Entity * oldParent;
	EntityParentChangedEvent() : entity(nullptr), newParent(nullptr), oldParent(nullptr) {}
	EntityParentChangedEvent(Entity * e, Entity * o, Entity * n) : entity(e), oldParent(o), newParent(n) {}
};