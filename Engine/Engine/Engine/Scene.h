#pragma once

#include <Engine\WidgetRenderer.h>
#include <ExportHeader.h>
#include <Engine\Renderer\Output\PassInfo.h>

class ENGINE_SHARED Scene {
public:
	const char * name;

	//when adding new renderables the default PassInfo will be this
	PassInfo * myDefaultPass;
	Scene(const char * name) { this->name = name; }
	virtual void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) = 0;
	virtual void update(float dt) = 0;
};