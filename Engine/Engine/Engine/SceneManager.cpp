#pragma once

#include "SceneManager.h"

void SceneManager::init() {
	for (int i = 0; i < scenes.size(); i++)
	{
		menu->setDefaultTab(scenes[i]->name);
		menu->watch("Scene name: ",scenes[i]->name);
		scenes[i]->myDefaultPass = addPassInfo(false);
		scenes[i]->myDefaultPass->cam.enabled = true;
		setDefaultPassInfo(scenes[i]->myDefaultPass);
		scenes[i]->init(this,scenes[i]->myDefaultPass->cam,menu);
		scenes[i]->myDefaultPass->visable = false;
		if(i==scenes.size()-1) {
			scenes[i]->myDefaultPass->visable = true;
			myCam = scenes[i]->myDefaultPass->cam;
			menu->setActiveTab(scenes[i]->name);
			activeScene = scenes[i];
		}
	}
}
void SceneManager::nextFrame(float dt) {
	const char * currentActiveScene = menu->getActiveTab();
	if(currentActiveScene != activeScene->name) {
		activeScene->myDefaultPass->visable = false;

		for (int i = 0; i < scenes.size(); i++)
		{
			if(currentActiveScene == scenes[i]->name) {
				scenes[i]->myDefaultPass->visable = true;
				activeScene = scenes[i];
				myCam = activeScene->myDefaultPass->cam;
				break; // no need to keep on
			}
		}
	}
	activeScene->myDefaultPass->cam = myCam;
	activeScene->update(dt);
	myCam = activeScene->myDefaultPass->cam;
}

void SceneManager::windowResized(int oldWidth,int oldHeight) {
	for (int i = 0; i < scenes.size(); i++)
	{
		scenes[i]->windowResized(width(),height());
	}
}

void SceneManager::addScene(Scene * toAdd) {
	scenes.push_back(toAdd);
}