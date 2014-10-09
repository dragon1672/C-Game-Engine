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
	for (uint i = 0; i < entities.size(); i++) {
		RenderableComponent * renderable = entities[i].getComponent<RenderableComponent>();
		if(renderable != nullptr && renderable->visable) {
			renderable->drawWarmup();
			renderer.draw(renderable->whatGeo);
		}
	}
}