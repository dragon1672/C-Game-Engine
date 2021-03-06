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
#include <Engine/Systems/Events/Events/GameEvents.h>
#include <Engine/Systems/Events/Events/EntityListChangedEvent.h>

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
bool GameObjectManager::initGl()
{
	glewInit();
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	resourceManager.PassDownToHardWare();
	emitEvent(new GLInited());
	return true;
}
bool GameObjectManager::start() {
	Timer::getInstance().start();
	for (uint i = 0; i < entities.size(); i++) { entities[i].start(); }
	emitEvent(new GameStarted());
	return true;
}
bool GameObjectManager::shutdown() {
	inputManager.delInstance();
	MasterLua::delInstance();
	resourceManager.shutdown();
	resourceManager.delInstance();
	Timer::delInstance();
	printer.delInstance();
	entities.clear();
	camManager.delInstance();
	eventManager.delInstance();
	return true;
}
void GameObjectManager::update() {
	Timer::getInstance().interval();
	inputManager.update();
	resourceManager.update();
	eventManager.update(Timer::getInstance().deltaTime());
	if(disable) return;
	for (uint i = 0; i < entities.size(); i++) { if(entities[i].GetActive() && (!selectorFunction || selectorFunction && selectorFunction(&entities[i]))) entities[i].earlyUpdate(); }
	emitEvent(new GameUpdate());
	for (uint i = 0; i < entities.size(); i++) { if(entities[i].GetActive() && (!selectorFunction || selectorFunction && selectorFunction(&entities[i]))) entities[i].update();      }
	for (uint i = 0; i < entities.size(); i++) { if(entities[i].GetActive() && (!selectorFunction || selectorFunction && selectorFunction(&entities[i]))) entities[i].lateUpdate();  }
}

void GameObjectManager::paint(std::function<void(int startX,int startY,int width,int height)> setViewPort) {
	setViewPort(0,0,width,height);
	glClearColor(.1f,.1f,.1f,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto cams = camManager.getAllActiveCams();
	if(cams.size() == 0) {
		printer.LogError("No camera in scene");
		return;
	}
	for (uint CamIndex = 0; CamIndex < cams.size(); CamIndex++)
	{
		CameraComponent * activeCam = cams[CamIndex];
		{
			float * t = &activeCam->clearColor[0]; //so I don't have to write out full thing 3 times
			glClearColor(t[0],t[1],t[2],1);
		}
		Dims tmp = activeCam->getDimsAsPixels();
		setViewPort((int)tmp.Start().x,(int)tmp.Start().y,(int)tmp.End().x,(int)tmp.End().y);
		glScissor((int)tmp.Start().x,(int)tmp.Start().y,(int)tmp.End().x,(int)tmp.End().y);
		glEnable(GL_SCISSOR_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);

		for (uint i = 0; i < entities.size(); i++) {
			Entity& currentEntity = entities[i];
			if(currentEntity.GetActive() && (!selectorFunction || selectorFunction && selectorFunction(&currentEntity))) {
				auto renderables = currentEntity.getComponents<RenderableComponent>();
				for (RenderableComponent * renderable : renderables) {
					if(renderable != nullptr && renderable->visable && renderable->isValid()) {
						passStandardUniforms(renderable, activeCam);
						renderable->drawWarmup();
						renderable->Geo()->paint();
					}
				}
			}
		}
	}
}

Entity * GameObjectManager::getNewEntity(std::string name) {
	Entity * ret = nullptr;
	entities.add(Entity(name,this));
	ret = &entities.back();
	return ret;
}

Entity * GameObjectManager::AddEntity(std::string name)
{
	Entity * ret = getNewEntity(name);
	
	EntityManager.Register(ret);
	emitEvent(new EntityAddedEvent(ret));
	emitEvent(new EntityListChangedEvent());
	return ret;
}

void GameObjectManager::passStandardUniforms(RenderableComponent * renderable, CameraComponent * cam)
{
	cam->getDims()->MasterDims((float)width,(float)height);
	ShaderProgram * prog = renderable->Shader();
	prog->useProgram();
	auto model2World = renderable->Parent()->getWorldTransform();
	auto world2cam = cam->getWorld2View();
	auto model2cam = world2cam * model2World;
	auto MVP = cam->getPerspective() * model2cam;
	prog->passUniform("model2WorldTransform",model2World);
	prog->passUniform("world2Cam",world2cam);
	prog->passUniform("model2Cam",model2cam);
	prog->passUniform("perspective",cam->getPerspective());
	prog->passUniform("MVP",MVP);
}

std::vector<Entity *> GameObjectManager::getTopLevelEntities()
{
	std::vector<Entity*> tmp;
	for (uint i = 0; i < entities.size(); i++)
		tmp.push_back(&entities[i]);
	return Collections::Where<Entity*>(tmp,[](Entity*& a){ return a->Parent() == nullptr; });
}

void GameObjectManager::RemoveEntity(double toRemove) {
	RemoveEntity(getEntity(toRemove));
}
void GameObjectManager::RemoveEntity(Entity * toRemove)
{
	int index = entities.find(toRemove);
	if(index >= 0) {
		Entity * toKill = &entities[index];
		for (auto i : toRemove->Children()) {
			RemoveEntity(i);
		}
		toKill->SetActive(false);

		toKill->Parent(nullptr);

		emitEvent(new EntityRemovedEvent(toRemove));
		toKill->shutdown();
		EntityManager.UnRegister(toRemove);
		entities.remove(toKill);
		emitEvent(new EntityListChangedEvent());
	}
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
		if(entities[i].GetActive() && !entities[i].ComponentsAreReady())
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
	s << entities;
	//s << ret;
}

void GameObjectManager::Load(Stream&s)
{
	Object::ObjectLoad(s);
	while(entities.size() > 0)
	{
		RemoveEntity(&entities.back());
	}
	entities.clear();
	s >> entities;
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
}

void GameObjectManager::Enable()
{
	disable = false;
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

Entity * GameObjectManager::CloneEntity(Entity * existingEntity, bool cloneChildren)
{
	if(existingEntity == nullptr) return nullptr;
	return existingEntity->Clone(cloneChildren);
}

Entity * GameObjectManager::CloneEntity(double toCloneId, bool cloneChildren /*= true*/)
{
	return CloneEntity(getEntity(toCloneId),cloneChildren);
}

GameObjectManager::operator LuaUserdata<GameObjectManager>()
{
	MAKE_LUA_INSTANCE_RET(GameObjectManager,ret);

	ret.Bind("getEntityFromName",&GameObjectManager::getEntityFromName);
	ret.Bind("getEntityFromId",&GameObjectManager::getEntityFromId);
	ret.Bind("Clone",&GameObjectManager::CloneFromEntity_LUA);

	return ret;
}

std::vector<Entity *> GameObjectManager::getAllEntities()
{
	std::vector<Entity *> ret;
	for (uint i = 0; i < entities.size(); i++) {
		ret.push_back(&entities[i]);
	}
	return ret;
}

Entity * GameObjectManager::CloneFromEntity(Entity * e, bool recursive /*= true*/)
{
	return CloneEntity(e,recursive);
}

Entity * GameObjectManager::CloneFromID(double e, bool recursive /*= true*/)
{
	return CloneEntity(e,recursive);
}
