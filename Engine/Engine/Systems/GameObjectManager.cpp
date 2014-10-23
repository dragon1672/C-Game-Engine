#include <gl\glew.h>
#include "GameObjectManager.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ResourceManager.h>
#include <Engine/Systems/InputManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Tools/CollectionEditing.h>
#include <string>

GameObjectManager::GameObjectManager() : active(false) {
	nearPlane.setter = [this](float& val, float&newGuy) { val = newGuy; perspectiveOutOfDate = true; };
	farPlane.setter  = [this](float& val, float&newGuy) { val = newGuy; perspectiveOutOfDate = true; };
	width.setter     = [this](int& val,   int&newGuy)   { val = newGuy; perspectiveOutOfDate = true; };
	height.setter    = [this](int& val,   int&newGuy)   { val = newGuy; perspectiveOutOfDate = true; };
	nearPlane = .1f;
	farPlane = 100;
}
bool GameObjectManager::init() {
	if(!active)
		cam.lookAt(glm::vec3(0,10,10),glm::vec3(0,0,0));
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
	if(perspectiveOutOfDate) updateViewTransform();

	glClearColor(.1f,.1f,.1f,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



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
	prog->useProgram();
	auto model2World = renderable->Parent()->getWorldTransform();
	auto world2cam = cam.getWorld2View();
	auto model2cam = world2cam * model2World;
	auto MVP = perspective * model2cam;
	prog->passUniform("model2WorldTransform",model2World);
	prog->passUniform("world2Cam",world2cam);
	prog->passUniform("model2Cam",model2cam);
	prog->passUniform("perspective",perspective);
	prog->passUniform("MVP",MVP);
}

void GameObjectManager::updateViewTransform()
{
	const float aspectRatio = (float)width/(float)height;
	perspective = glm::perspective(60.0f,aspectRatio,(float)nearPlane,(float)farPlane);
	perspectiveOutOfDate = false;
}

std::vector<Entity *> GameObjectManager::getTopLevelEntities()
{
	//ConstVec<Entity> entities <- class of my creation bascally an array of Entities
	//return Collections::Where<Entity*>(Collections::Select<Entity,Entity*>(entities,[](Entity& dude){return &dude;}),[](Entity*& a){ return a->Parent() == nullptr; });
	std::vector<Entity*> tmp;
	for (uint i = 0; i < entities.size(); i++)
		tmp.push_back(&entities[i]);
	return Collections::Where<Entity*>(tmp,[](Entity*& a){ return a->Parent() == nullptr; });
}
