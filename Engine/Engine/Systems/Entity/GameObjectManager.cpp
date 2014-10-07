#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() : active(false) {}
bool GameObjectManager::init() {
	if(!active)
		for (int i = 0; i < entities.size(); i++) {
			entities[i]->init();
		}
		Timer::getInstance().start();
}
bool GameObjectManager::shutdown() {

}
void GameObjectManager::update() {
	Timer::getInstance().interval();
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->earlyUpdate();
	}
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->update();
	}
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->lateUpdate();
	}
}
void GameObjectManager::paint() {
	for (int i = 0; i < entities.size(); i++) {
		RenderableComponent * renderable = entities[i]->getComponent<RenderableComponent>();
		if(renderable != nullptr && renderable->visable) {
			renderable->drawWarmup();
			renderer.draw(renderable->whatGeo);
		}
	}
}