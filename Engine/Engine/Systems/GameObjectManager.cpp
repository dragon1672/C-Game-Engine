#include <gl\glew.h>
#include "GameObjectManager.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ResourceManager.h>
#include <Engine/Systems/InputManager.h>
#include <glm/gtc/matrix_transform.hpp>

GameObjectManager::GameObjectManager() : active(false) {
	nearPlane.setter = [this](float& val, float&newGuy) { val = newGuy; updateViewTransform(); };
	farPlane.setter  = [this](float& val, float&newGuy) { val = newGuy; updateViewTransform(); };
	width.setter     = [this](int& val, int&newGuy) { val = newGuy; updateViewTransform(); };
	height.setter    = [this](int& val, int&newGuy) { val = newGuy; updateViewTransform(); };
	nearPlane = .1f;
	farPlane = 100;
}
bool GameObjectManager::init() {
	if(!active)
		MasterLua::getInstance().init();
		resourceManager.init();
		for (uint i = 0; i < entities.size(); i++) {
			entities[i].init();
		}
		Timer::getInstance().start();
		inputManager.init();
		return true;
}
bool GameObjectManager::start() {
	for (uint i = 0; i < entities.size(); i++) { entities[i].start(); }
	return true;
}
bool GameObjectManager::shutdown() {
	return true;
}
void GameObjectManager::update() {
	inputManager.update();
	Timer::getInstance().interval();
	resourceManager.update();
	for (uint i = 0; i < entities.size(); i++) { entities[i].earlyUpdate(); }
	for (uint i = 0; i < entities.size(); i++) { entities[i].update();      }
	for (uint i = 0; i < entities.size(); i++) { entities[i].lateUpdate();  }
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
			passStandardUniforms(renderable);
			renderable->drawWarmup();
			renderable->whatGeo->paint();
		}
	}
}

Entity * GameObjectManager::AddEntity(const char * name)
{
	entities.add(Entity(name));
	return &entities.last();
}

bool GameObjectManager::initGl()
{
	glewInit();
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	resourceManager.PassDownToHardWare();
	return true;
}

void GameObjectManager::passStandardUniforms(RenderableComponent * renderable)
{
	ShaderProgram * prog = renderable->howShader;
	auto model2World = renderable->Parent()->getWorldTransform();
	auto world2cam = cam.getWorld2View();
	auto model2cam = world2cam * model2World;
	auto MVP = viewTransform * model2cam;
	prog->passUniform("model2WorldTransform",model2World);
	prog->passUniform("world2Cam",world2cam);
	prog->passUniform("model2Cam",model2cam);
	prog->passUniform("viewTransform",viewTransform);
	prog->passUniform("MVP",MVP);
}

void GameObjectManager::updateViewTransform()
{
	const float aspectRatio = (float)width/(float)height;
	viewTransform = glm::perspective(60.0f,aspectRatio,(float)nearPlane,(float)farPlane);
}
