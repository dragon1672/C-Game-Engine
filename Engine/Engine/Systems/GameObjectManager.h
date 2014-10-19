#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Tools/Timer.h>
#include <Engine/Systems/Resources/TextureInfo.h>
#include <Engine/Defines/SingletonsDefine.h>
#include <Engine/Tools/MasterLua.h>

#include <Engine/Tools/ConstVector.h>
#include <Engine/Systems/Resources/Mesh.h>
#include <ExportHeader.h>

class ENGINE_SHARED GameObjectManager {
private:
	ConstVector<Entity> entities;
	
	bool active;

	void passDataDownAllShaders_force();
	void passDataDownAllShaders_try();
	void resetAllShaders_validPush();
public:

	//add
	Entity * AddEntity(const char * name = "GameObject");



	GameObjectManager();
	bool init(); // called with object is created
	bool initGl();
	bool start(); // called when scene is loaded
	bool shutdown();
	void update();
	void paint();
};