#pragma once

#include <Engine\Systems\WidgetRenderer.h>
#include <vector>
#include <Engine\Systems\Scene.h>
#include <ExportHeader.h>

class ENGINE_SHARED SceneManager : public WidgetRenderer {
	std::vector<Scene *> scenes;
	Scene * activeScene;

	//overrides
	void init();
	void nextFrame(float dt);
	void windowResized(int oldWith, int oldHeight);
public:
	void addScene(Scene * toAdd);
};