#pragma once

#include "SceneManager.h"

void SceneManager::init() {
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
void SceneManager::nextFrame(float dt) {
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
void SceneManager::addScene(Scene * toAdd) {
		scenes.push_back(toAdd);
	}