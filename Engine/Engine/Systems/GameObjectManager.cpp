#include "GameObjectManager.h"
#include <Engine/Entity/Entity.h>

GameObjectManager::GameObjectManager() : active(false) {}
bool GameObjectManager::init() {
	if(!active)
		for (uint i = 0; i < entities.size(); i++) {
			entities[i].init();
		}
		Timer::getInstance().start();
		return true;
}
bool GameObjectManager::shutdown() {
	return true;
}
void GameObjectManager::update() {
	Timer::getInstance().interval();
	for (uint i = 0; i < entities.size(); i++) {
		entities[i].earlyUpdate();
	}
	for (uint i = 0; i < entities.size(); i++) {
		entities[i].update();
	}
	for (uint i = 0; i < entities.size(); i++) {
		entities[i].lateUpdate();
	}
}
void GameObjectManager::paint() {
	/*
	if(clear) {
		float clearX = toDraw.clearColor.x;
		float clearY = toDraw.clearColor.y;
		float clearZ = toDraw.clearColor.z;
		glClearColor(clearX,clearY,clearZ,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	const float aspectRatio = (float)width()/(float)height();
	perspectiveMat = glm::perspective(60.0f,aspectRatio,nearPlane,farPlane);
	viewTransform = perspectiveMat;
	viewTransform *= toDraw.cam.enabled ? toDraw.cam.getWorld2View() : myCam.getWorld2View();
	viewTransform *= additionalViewTransform;
	//*/

	for (uint i = 0; i < entities.size(); i++) {
		RenderableComponent * renderable = entities[i].getComponent<RenderableComponent>();
		if(renderable != nullptr && renderable->visable) {
			renderable->drawWarmup();
			renderer.draw(renderable->whatGeo);
		}
	}
}

Entity * GameObjectManager::AddEntity(const char * name)
{
	entities.add(Entity(name));
	return &entities.last();
}