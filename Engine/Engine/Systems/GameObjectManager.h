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
#include <Engine/Tools/PropertyWrapper.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/ObjectManager.h>

#include <Engine/Systems/CameraManager.h>

class ENGINE_SHARED GameObjectManager {
private:
public:ConstVector<Entity> entities;

	bool active;

	void passDataDownAllShaders_force();
	void passDataDownAllShaders_try();
	void resetAllShaders_validPush();
public:
	std::vector<std::function<void(Entity*)>> entityAddEvent;
	std::vector<std::function<void(Entity*)>> entityRemoveEvent;
	std::vector<std::function<void(Entity*)>> entityListChange;
	std::vector<Entity *> getTopLevelEntities();
	//add
	Entity * AddEntity(const char * name = "GameObject");
	void RemoveEntity(Entity * toRemove);
	int width;
	int height;

	GameObjectManager();
	bool init(); // called before openGL, setup cars
	bool initGl(); // pass data down to HW
	bool start(); // called when scene is loaded (use for setting variable starting values)
	bool shutdown();
	void update();
	void paint();
private:
	void passStandardUniforms(RenderableComponent * renderable);
};