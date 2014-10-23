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

class Component;

class ENGINE_SHARED Entity : public Object {
private:
	void removeComponent(int toKill);
	template<typename T> int getIndex() {
		return getIndex(typeid(T).name());
	}
	int getIndex(Component * toFind);
	int getIndex(const char * toFind);
	int getIndex(std::string toFind);

	Entity * parent;
	std::unordered_set<Entity *> children;
public:
	Entity * Parent();
	void Parent(Entity * newGuy);


	Entity(const char * name="New Game Object", Entity * p = nullptr);
	const char * getName();
	virtual ~Entity(){}

	std::vector<Component *> components;
	glm::mat4 getWorldTransform();
	MatrixInfo localTrans;

	MatrixInfo * getTrans();
	RenderableComponent * getRenderable();
	ScriptComponent * getScript();

	template<typename T> T* addComponent() { return (T*)addComponent(new T()); }
	template<typename T> T* addComponent(const char * data) { return (T*)addComponent(new T(data)); }
	template<typename T> T* addComponent(Resource * data)   { return (T*)addComponent(new T(data)); }
	template<typename T> T* addComponent(int resouceId)     { return (T*)addComponent(new T(resouceId)); }
	template<typename T> T* addComponent(std::string  data) { return (T*)addComponent(new T(data)); }
	Component* addComponent(Component * toAdd);
	template<typename T> void removeComponent() {
		removeComponent(getIndex<T>()); 
	}
	template<class T> T* getComponent(std::string name) {
		int index = getIndex(name);
		return (index <= 0) ? (T*)components[index] : nullptr;
	}
	template<class T> T* getComponent() {
		int index = getIndex<T>();
		return (index <= 0) ? (T*)components[index] : nullptr;
	}
	void removeComponent(Component * toKill);
	void init();
	void start(); // called after openGL, every time scene loads, before update
	void earlyUpdate();
	void update();
	void lateUpdate();

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

