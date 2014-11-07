#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Entity/Component.h>

class ComponentRemovedEvent : public EventData {
public:
	Entity * entity;
	Component * beingTrashed;
	ComponentRemovedEvent() : entity(nullptr), beingTrashed(nullptr) {}
	ComponentRemovedEvent(Entity * e, Component * c) : entity(e), beingTrashed(c) {}
};