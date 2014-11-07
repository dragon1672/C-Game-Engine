#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Entity/Component.h>

class ComponentAddedEvent : public EventData {
public:
	Entity * entity;
	Component * beingAdded;
	ComponentAddedEvent() : entity(nullptr), beingAdded(nullptr) {}
	ComponentAddedEvent(Entity * e, Component * c) : entity(e), beingAdded(c) {}
};