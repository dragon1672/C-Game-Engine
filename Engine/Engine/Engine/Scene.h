#pragma once

#include <Engine\WidgetRenderer.h>
#include <ExportHeader.h>
#include <Engine\Renderer\Output\PassInfo.h>

class ENGINE_SHARED Scene {
protected: // some helpful functions
	void resetPassInfo(WidgetRenderer * renderer) {
		renderer->setDefaultPassInfo(myDefaultPass);
	}
public:
	const char * name;

	//when adding new renderables the default PassInfo will be this
	PassInfo * myDefaultPass;


	//          ------------------      WHAT YOU NEED TO IMPLEMENT           ------------------      //

	// make your own constructor and name your scene
	Scene(const char * name) : name(name) {}
	virtual void init(WidgetRenderer * renderer, Camera& myCam, DebugMenuManager * menu) = 0;
	virtual void update(float dt) = 0;
};