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

	std::unordered_set<int> deletedEntities;

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
	std::function<bool(Entity*)> SelectorFunction() const;
	void SelectorFunction(std::function<bool(Entity*)> val);
	std::function<bool(Component*)> ComponentSelectorFunction() const;
	void ComponentSelectorFunction(std::function<bool(Component*)> val);

	std::vector<Entity *> getTopLevelEntities();
	//add
	Entity * AddEntity(std::string name = "GameObject");
	void RemoveEntity(Entity * toRemove);
	void RemoveEntity(double toRemove);

	Entity * getEntity(std::string name) {
		return (Entity*)EntityManager.getFirst(name.c_str());
	}
	Entity * getEntity(double id) {
		return (Entity*)EntityManager.getFirst(id);
	}
	//will copy components
	Entity * CloneEntity(int toCloneId) {
		Entity * e = getEntity(toCloneId);
		auto n = AddEntity(e->Name());

		//clone all components ... somehow :/
		return n;
	}
	int width;
	int height;

	GameObjectManager();
	~GameObjectManager();

	bool init(); // called before openGL, setup cars
	bool initGl(); // pass data down to HW
	bool start(); // called when scene is loaded (use for setting variable starting values)
	bool shutdown();
	void update();
	void paint();
	bool Valid();
	std::vector<std::string> getErrors();

	inline operator LuaUserdata<GameObjectManager>() {
		MAKE_LUA_INSTANCE_RET(GameObjectManager,ret);

		ret.Bind("getEntityFromName",&GameObjectManager::getEntityFromName);
		ret.Bind("getEntityFromId",&GameObjectManager::getEntityFromId);

		return ret;
	}
	virtual void Save(Stream&s);

	virtual void Load(Stream&s);
private:
	void passStandardUniforms(RenderableComponent * renderable);

};