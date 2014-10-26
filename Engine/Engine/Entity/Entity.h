#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <ExportHeader.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ObjectManager.h>
#include <unordered_set>


#include <Engine/Tools/MatrixInfo.h>
#include <Engine/Entity/Components/ScriptComponent.h>

class RenderableComponent;
class GameObjectManager;
class Component;
class CameraComponent;

class ENGINE_SHARED Entity : public Object {
private:
	void removeComponent(int toKill);
	template<typename T> int getIndex() {
		return getIndexFromClassName(typeid(T).name());
	}
	int getIndex(Component * toFind);
	int getIndex(const char * toFind);
	int getIndexFromClassName(const char * toFind);
	int getIndex(std::string toFind);
	std::vector<int> getAllFromClassName(const char * toFind);
	template<typename T> std::vector<int> getAllIndexs() {
		return getAllFromClassName(typeid(T).name());
	}


	Entity * parent;
	GameObjectManager * manager;
	Component* addComponent(Component * toAdd);
	std::unordered_set<Entity *> children;
public:
	std::unordered_set<Entity *> Children();
	std::vector<std::function<void(Entity*oldParent,Entity*newParent)>> parentChangedEvent;
	Entity * Parent();
	void Parent(Entity * newGuy);

	std::unordered_set<Entity *> getAllChildren();


	Entity(const char * name="New Game Object", GameObjectManager * manager = nullptr, Entity * p = nullptr);
	const char * getName();
	virtual ~Entity(){}

	std::vector<Component *> components;
	glm::mat4 getWorldTransform();
	MatrixInfo localTrans;

	MatrixInfo * getTrans();
	RenderableComponent * getRenderable();
	ScriptComponent * getScript();

	template<typename T> T* addComponent() { return (T*)addComponent(new T()); }
	template<typename T> void removeComponent() {
		removeComponent(getIndex<T>()); 
	}
	template<class T> T* getComponent(std::string name) {
		int index = getIndex(name);
		return (index <= 0) ? (T*)components[index] : nullptr;
	}
	template<class T> T* getComponent() {
		int index = getIndex<T>();
		return (index >= 0) ? (T*)components[index] : nullptr;
	}
	template<class T> std::vector<T*> getComponents() {
		std::vector<int> tmp = getAllIndexs<T>();
		auto vec = Collections::Select<int,Component*>(tmp,[this](int index) {return components[index];} );
		return Collections::RICVec<T*>(vec);
	}

	template<> RenderableComponent* addComponent();
	template<> CameraComponent* addComponent();
	void removeComponent(Component * toKill);
	void init();
	void start(); // called after openGL, every time scene loads, before update
	void earlyUpdate();
	void update();
	void lateUpdate();

	bool ComponentsAreReady();

	GET_LUA_VER_PTR(Entity,parent);
	LUA_GET_FUN_PTR(MatrixInfo,getTrans);
	LUA_GET_FUN_PTR(ScriptComponent,getScript);

	inline operator LuaUserdata<Entity>() const {
		MAKE_LUA_INSTANCE_RET(Entity,ret);

		BIND_LUA_VER(Entity,ret,parent);
		LUA_BIND_FUN(Entity,ret,getTrans);
		LUA_BIND_FUN(Entity,ret,getScript);
		ret.Bind("name",&Entity::getName);

		return ret;
	}
};

