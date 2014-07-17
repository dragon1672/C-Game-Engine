#pragma once

#include <Engine\WidgetRenderer.h>
#include <vector>
#include "Scene.h"

class SceneManager : public WidgetRenderer {
	std::vector<Scene *> scenes;
	Scene * activeScene;

	//overrides
	void init() {
		for (int i = 0; i < scenes.size(); i++)
		{
			menu->setDefaultTab(scenes[i]->name);
			menu->watch("Scene name: ",scenes[i]->name);
			scenes[i]->init(this,myCam,menu);
			scenes[i]->disable();
			if(i==scenes.size()-1) {
				scenes[i]->enable();
				menu->setActiveTab(scenes[i]->name);
				activeScene = scenes[i];
			}
		}
	}
	void nextFrame(float dt) {
		if(!menu->isActiveTab(activeScene->name)) {
			for (int i = 0; i < scenes.size(); i++)
			{
				if(menu->isActiveTab(scenes[i]->name)) {
					scenes[i]->enable();
					activeScene = scenes[i];
				} else {
					scenes[i]->disable();
				}
			}
		}
		activeScene->update(dt);
	}
public:
	void addScene(Scene * toAdd) {
		scenes.push_back(toAdd);
	}
};