#include <gl\glew.h>
#include "GameObjectManager.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ResourceManager.h>
#include <Engine/Systems/InputManager.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Tools/CollectionEditing.h>
#include <string>
#include <Engine/Tools/Printer.h>

GameObjectManager::GameObjectManager() {
	entityAddEvent.push_back([this](Entity* e){ for(uint i=0;i<entityListChange.size();i++) entityListChange[i](e); });
	entityRemoveEvent.push_back([this](Entity* e){ for(uint i=0;i<entityListChange.size();i++) entityListChange[i](e); });
}
bool GameObjectManager::init() {
	MasterLua::getInstance().init();
	resourceManager.init();
	for (uint i = 0; i < entities.size(); i++) {
		if(entities[i].active) entities[i].init();
	}
	inputManager.init();
	return true;
}
bool GameObjectManager::start() {
	for (uint i = 0; i < entities.size(); i++) {
		if(entities[i].active && !entities[i].ComponentsAreReady())
			throw std::invalid_argument("Some component is not init");
	}
	Timer::getInstance().start();
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
	if(selectorFunction) {
		for (uint i = 0; i < entities.size(); i++) { if(entities[i].active && selectorFunction(&entities[i])) entities[i].earlyUpdate(); }
		for (uint i = 0; i < entities.size(); i++) { if(entities[i].active && selectorFunction(&entities[i])) entities[i].update();      }
		for (uint i = 0; i < entities.size(); i++) { if(entities[i].active && selectorFunction(&entities[i])) entities[i].lateUpdate();  }
	} else {
		for (uint i = 0; i < entities.size(); i++) { if(entities[i].active) entities[i].earlyUpdate(); }
		for (uint i = 0; i < entities.size(); i++) { if(entities[i].active) entities[i].update();      }
		for (uint i = 0; i < entities.size(); i++) { if(entities[i].active) entities[i].lateUpdate();  }
	}
}

void GameObjectManager::paint() {
	CameraComponent * current = camManager.ActiveCam();
	if(current == nullptr) {
		printer.LogError("No camera in scene");
		return;
	}
	glClearColor(.1f,.1f,.1f,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (uint i = 0; i < entities.size(); i++) {
		if(entities[i].active) {
			auto renderables = entities[i].getComponents<RenderableComponent>();
			for (RenderableComponent * renderable : renderables) {
				if(renderable != nullptr && renderable->visable && renderable->isValid()) {
					passStandardUniforms(renderable);
					renderable->drawWarmup();
					renderable->geo->paint();
				}
			}
		}
	}
}

Entity * GameObjectManager::AddEntity(const char * name)
{
	entities.add(Entity(name));
	Entity * ret = &entities.last();
	ret->StageChanged.push_back([this,ret](Entity* e){ for(uint i=0;i<entityListChange.size();i++) entityListChange[i](ret); });
	for (uint i = 0; i < entityAddEvent.size(); i++) entityAddEvent[i](ret);
	if(componentSelectorFunction) ret->SelectorFunction(componentSelectorFunction);
	return ret;
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
	camManager.ActiveCam()->width = width;
	camManager.ActiveCam()->height = height;
	ShaderProgram * prog = renderable->shader;
	prog->useProgram();
	auto model2World = renderable->Parent()->getWorldTransform();
	auto world2cam = camManager.ActiveCam()->getWorld2View();
	auto model2cam = world2cam * model2World;
	auto MVP = camManager.ActiveCam()->getPerspective() * model2cam;
	prog->passUniform("model2WorldTransform",model2World);
	prog->passUniform("world2Cam",world2cam);
	prog->passUniform("model2Cam",model2cam);
	prog->passUniform("perspective",camManager.ActiveCam()->getPerspective());
	prog->passUniform("MVP",MVP);
}

std::vector<Entity *> GameObjectManager::getTopLevelEntities()
{
	std::vector<Entity*> tmp;
	for (uint i = 0; i < entities.size(); i++)
		tmp.push_back(&entities[i]);
	return Collections::Where<Entity*>(tmp,[](Entity*& a){ return a->active && a->Parent() == nullptr; });
}

void GameObjectManager::RemoveEntity(Entity * toRemove)
{
	int index = entities.find(toRemove);
	if(index >= 0) {
		for (auto i : toRemove->Children()) {
			RemoveEntity(i);
		}
		entities[index].active = false;
		for (uint i = 0; i < entityRemoveEvent.size(); i++) entityRemoveEvent[i](toRemove);
	}
}

void GameObjectManager::ComponentSelectorFunction(std::function<bool(Component*)> val)
{
	componentSelectorFunction = val;
	for (uint i = 0; i < entities.size(); i++) {
		entities[i].SelectorFunction(val);
	}
}

std::function<bool(Component*)> GameObjectManager::ComponentSelectorFunction() const
{
	return componentSelectorFunction;
}

void GameObjectManager::SelectorFunction(std::function<bool(Entity*)> val)
{
	selectorFunction = val;
}

std::function<bool(Entity*)> GameObjectManager::SelectorFunction() const
{
	return selectorFunction;
}
