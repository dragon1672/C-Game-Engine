#pragma once

#include <Engine\WidgetRenderer.h>
#include <ExportHeader.h>

class ENGINE_SHARED Scene {
public:
	const char * name;
	Scene(const char * name) { this->name = name; }
	virtual void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual void update(float dt) = 0;
};