#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Tools/Timer.h>

class GameObjectManager {
private:
	std::vector<Entity*> entities;
	Renderer renderer;
	bool active;
public:
	GameObjectManager() : active(false) {}
	bool init() {
		if(!active)
		for (int i = 0; i < entities.size(); i++) {
			entities[i]->init();
		}
		Timer::getInstance().start();
	}
	bool shutdown() {

	}
	void update() {
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
	void paint() {
		for (int i = 0; i < entities.size(); i++) {
			RenderableComponent * renderable = entities[i]->getComponent<RenderableComponent>();
			if(renderable != nullptr && renderable->visable) {
				renderable->drawWarmup();
				renderer.draw(renderable->whatGeo);
			}
		}
	}
};