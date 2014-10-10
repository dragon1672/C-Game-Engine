#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Tools/Timer.h>
#include <Engine/Renderer/TextureInfo.h>
#include <Engine/Defines/SingletonsDefine.h>

#include <Engine/Tools/ConstVector.h>

class GameObjectManager {
private:
	DEFINE_SINGLETON(GameObjectManager);

	ConstVector<Entity> entities;
	ConstVector<TextureInfo> textures;
	
	Renderer renderer;
	bool active;
public:

	Entity * AddEntity();



	GameObjectManager();
	bool init();
	bool shutdown();
	void update();
	void paint();
};