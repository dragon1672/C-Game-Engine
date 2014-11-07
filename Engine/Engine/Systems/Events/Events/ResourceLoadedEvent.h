#pragma once

#include <Engine/Systems/Events/EventData.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Entity/Component.h>

class ResourceLoadedEvent : public EventData {
public:
	Resource * resource;
	ResourceLoadedEvent(Resource * resource = nullptr) : resource(resource) {}
};