#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Entity/Components/RenderableComponent.h>
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
#include <Engine/Tools/MasterLua.h>
#include <Engine/IO/StreamableObject.h>

#include <Engine/Systems/CameraManager.h>

#define gameManager GameObjectManager::getInstance()

class ENGINE_SHARED GameObjectManager : public Object, public StreamableObject {
	DEFINE_SINGLETON(GameObjectManager);
	LUA_OBJECT(GameObjectManager);
	ConstVector<Entity> entities;
	ObjectManager EntityManager;

	std::function<bool(Entity*)> selectorFunction;
	std::function<bool(Component*)> componentSelectorFunction;

	LuaUserdata<Entity> getEntityFromName(std::string name);
	LuaUserdata<Entity> getEntityFromId(int id);
	void rebuildEntityParents();
	Entity * getNewEntity(std::string name);
	bool disable;
public:
	void Enable();
	void Disable();

	int getTagVal(std::string val) {
		return -1;
	}
	int numberOfObjectsByType(std::string val) {
		return numberOfObjectsByType(getTagVal(val));
	}
	int numberOfObjectsByType(int val) {
		return -1;
	}
	Entity * getOfEntityByType(std::string val,int index) {
		return getOfEntityByType(getTagVal(val),index);
	}
	Entity * getOfEntityByType(int val,int index) {
		return nullptr;
	}

	std::function<bool(Entity*)> SelectorFunction() const;
	void SelectorFunction(std::function<bool(Entity*)> val);

	std::vector<Entity *> getTopLevelEntities();
	//add
	Entity * AddEntity(std::string name = "GameObject");
	void RemoveEntity(Entity * toRemove);
	void RemoveEntity(double toRemove);

	Entity * getEntity(std::string name);
	Entity * getEntity(double id);
	//will copy components
	Entity * CloneEntity(double  toCloneId, bool cloneChildren = true);
	Entity * CloneEntity(Entity * toClone,  bool cloneChildren = true);
	Entity * CloneFromEntity(Entity * e, bool recursive = true);
	Entity * CloneFromID(double e, bool recursive = true);
	LuaUserdata<Entity> CloneFromEntity_LUA(LuaUserdata<Entity> e, bool recursive = true) { return *CloneEntity(e->getID(),recursive); }
	int width;
	int height;

	GameObjectManager();
	~GameObjectManager();

	bool init(); // called before openGL, setup cars
	bool initGl(); // pass data down to HW
	bool start(); // called when scene is loaded (use for setting variable starting values)
	bool shutdown();
	void update();
	void paint(std::function<void(int startX,int startY,int width,int height)> setViewPort);
	bool Valid();
	std::vector<std::string> getErrors();
	std::vector<Entity *> getAllEntities();

	operator LuaUserdata<GameObjectManager>();
	virtual void Save(Stream&s);

	virtual void Load(Stream&s);

private:
	void passStandardUniforms(RenderableComponent * renderable, CameraComponent * cam);

};