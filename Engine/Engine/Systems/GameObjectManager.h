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

#include <Engine/Tools/Camera.h>

class ENGINE_SHARED GameObjectManager {
private:
	ConstVector<Entity> entities;

	bool active;

	Camera cam;
	glm::mat4 perspective;
	void updateViewTransform();
	bool perspectiveOutOfDate;

	void passDataDownAllShaders_force();
	void passDataDownAllShaders_try();
	void resetAllShaders_validPush();
public:
	std::vector<Entity *> getTopLevelEntities();
	//add
	Entity * AddEntity(const char * name = "GameObject");
	PropertyGetSet<int> width;
	PropertyGetSet<int> height;
	PropertyGetSet<float> nearPlane;
	PropertyGetSet<float> farPlane;
	

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