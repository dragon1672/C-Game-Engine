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
	GameObjectManager();
	bool init();
	bool shutdown();
	void update();
	void paint();
};