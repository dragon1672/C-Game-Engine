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
#include <Engine/Defines/Vectors.h>
#include <Engine/Tools/Printer.h>
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/IO/Stream.h>
#include <Engine/DebugTools/DebugMemHeader.h>

//events
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/EntityAddedEvent.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>

IMPLEMENT_SINGLETON(GameObjectManager);

GameObjectManager::GameObjectManager() :disable(false) {
	LUA_OBJECT_START(GameObjectManager);
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
	Timer::getInstance().start();
	for (uint i = 0; i < entities.size(); i++) { entities[i].start(); }
	return true;
}
bool GameObjectManager::shutdown() {
	inputManager.delInstance();
	MasterLua::delInstance();
	resourceManager.shutdown();
	resourceManager.delInstance();
	camManager.delInstance();
	Timer::delInstance();
	printer.delInstance();
	entities.clear();
	eventManager.delInstance();
	return true;
}
void GameObjectManager::update() {
	Timer::getInstance().interval();
	inputManager.update();
	resourceManager.update();
	eventManager.update(Timer::getInstance().deltaTime());
	if(disable) return;
	for (uint i = 0; i < entities.size(); i++) { if(entities[i].active && (!selectorFunction || selectorFunction && selectorFunction(&entities[i]))) entities[i].earlyUpdate(); }
	for (uint i = 0; i < entities.size(); i++) { if(entities[i].active && (!selectorFunction || selectorFunction && selectorFunction(&entities[i]))) entities[i].update();      }
	for (uint i = 0; i < entities.size(); i++) { if(entities[i].active && (!selectorFunction || selectorFunction && selectorFunction(&entities[i]))) entities[i].lateUpdate();  }
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
		Entity& currentEntity = entities[i];
		if(currentEntity.active && (!selectorFunction || selectorFunction && selectorFunction(&currentEntity))) {
			auto renderables = currentEntity.getComponents<RenderableComponent>();
			for (RenderableComponent * renderable : renderables) {
				if(renderable != nullptr && renderable->visable && renderable->isValid()) {
					passStandardUniforms(renderable);
					renderable->drawWarmup();
					renderable->Geo()->paint();
				}
			}
		}
	}
}

Entity * GameObjectManager::getNewEntity(std::string name) {
	Entity * ret = nullptr;
	for (auto itr = deletedEntities.begin(); ret == nullptr && itr != deletedEntities.end();) {
		int e = *itr;
		itr++;
		deletedEntities.erase(e);
		if((unsigned)e >= entities.size()) continue;
		entities[e] = Entity(name,this);
		ret = &entities[e];
	}
	if(ret == nullptr) {
		entities.add(Entity(name,this));
		ret = &entities.back();
	}
	return ret;
}

Entity * GameObjectManager::AddEntity(std::string name)
{
	Entity * ret = getNewEntity(name);
	
	EntityManager.Register(ret);
	emitEvent(new EntityAddedEvent(ret));
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
	if(camManager.ActiveCam() == nullptr) {
		printErr(100) "No cam in scene";
		return;
	}
	camManager.ActiveCam()->width = width;
	camManager.ActiveCam()->height = height;
	ShaderProgram * prog = renderable->Shader();
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

void GameObjectManager::RemoveEntity(double toRemove) {
	RemoveEntity(getEntity(toRemove));
}
void GameObjectManager::RemoveEntity(Entity * toRemove)
{
	int index = entities.find(toRemove);
	if(index >= 0) {
		for (auto i : toRemove->Children()) {
			RemoveEntity(i);
		}
		entities[index].active = false;
		entities[index].Parent(nullptr);
		emitEvent(new EntityRemovedEvent(toRemove));
	}
	if((unsigned)index == entities.size()-1) entities.pop_back();
	else deletedEntities.emplace(index);
	EntityManager.UnRegister(toRemove);
}

void GameObjectManager::SelectorFunction(std::function<bool(Entity*)> val)
{
	selectorFunction = val;
}

std::function<bool(Entity*)> GameObjectManager::SelectorFunction() const
{
	return selectorFunction;
}

bool GameObjectManager::Valid()
{
	for (uint i = 0; i < entities.size(); i++) {
		if(entities[i].active && !entities[i].ComponentsAreReady())
			return false;
	}
	return true;
}

std::vector<std::string> GameObjectManager::getErrors()
{
	std::vector<std::string> ret;
	for (uint i = 0; i < entities.size(); i++) { Collections::AddToFirstVector(ret,entities[i].getErrors()); }
	return ret;
}

GameObjectManager::~GameObjectManager()
{
	LUA_OBJECT_END(GameObjectManager);
	shutdown();
}

void GameObjectManager::Save(Stream&s)
{
	//std::vector<Entity *> ret;
	//for (uint i = 0; i < entities.size(); i++) {
	//	ret.push_back(&entities[i]);
	//}
	//ret;
	Object::ObjectSave(s);
	//s << ret;
	s << getAllEntities();
}

void GameObjectManager::Load(Stream&s)
{
	Object::ObjectLoad(s);
	s >> entities;
	deletedEntities.clear();
	EntityManager.ClearAll();
	EntityManager.Register(Collections::Select<Entity,Object*>(entities,[](Entity&e){ return &e; }));
	for (uint i = 0; i < entities.size(); i++) {
		emitEvent(new EntityAddedEvent(&entities[i]));
	}
	rebuildEntityParents();
}

void GameObjectManager::rebuildEntityParents()
{
	for (uint i = 0; i < entities.size(); i++) {
		entities[i].resetChildren();
	}
	for (uint i = 0; i < entities.size(); i++) {
		Entity * dude = &entities[i];
		Entity * parent = dude->Parent();
		dude->Parent(parent);
	}
}

void GameObjectManager::Disable()
{
	disable = true;
	eventManager.Disable();
}

void GameObjectManager::Enable()
{
	disable = false;
	eventManager.Enable();
}

LuaUserdata<Entity> GameObjectManager::getEntityFromName(std::string name)
{
	return (LuaUserdata<Entity>)*getEntity(name);
}

LuaUserdata<Entity> GameObjectManager::getEntityFromId(int id)
{
	return (LuaUserdata<Entity>)*getEntity(id);
}

Entity * GameObjectManager::getEntity(double id)
{
	return (Entity*)EntityManager.getFirst(id);
}

Entity * GameObjectManager::getEntity(std::string name)
{
	return (Entity*)EntityManager.getFirst(name.c_str());
}

Entity * GameObjectManager::CloneEntity(int toCloneId)
{
	Entity * e = getEntity(toCloneId);
	auto n = AddEntity(e->Name());

	//clone all components ... somehow :/
	return n;
}

GameObjectManager::operator LuaUserdata<GameObjectManager>()
{
	MAKE_LUA_INSTANCE_RET(GameObjectManager,ret);

	ret.Bind("getEntityFromName",&GameObjectManager::getEntityFromName);
	ret.Bind("getEntityFromId",&GameObjectManager::getEntityFromId);

	return ret;
}

std::vector<Entity *> GameObjectManager::getAllEntities()
{
	std::vector<Entity *> ret;
	for (uint i = 0; i < entities.size(); i++) {
		if(deletedEntities.find(i) == deletedEntities.end()) {
			ret.push_back(&entities[i]);
		}
	}
	return ret;
}
