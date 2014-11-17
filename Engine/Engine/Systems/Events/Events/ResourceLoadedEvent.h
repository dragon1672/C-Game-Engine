#pragma once

#include <Engine/Systems/Events/EventData.h>

class Entity;
class Component;

class ResourceLoadedEvent : public EventData {
public:
	Resource * resource;
	ResourceLoadedEvent(Resource * resource = nullptr) : resource(resource) {}
};