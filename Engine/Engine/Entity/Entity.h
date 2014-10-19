#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <ExportHeader.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ObjectManager.h>


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
public:
	Entity * parent;

	Entity(const char * name="New Game Object", Entity * p = nullptr);
	const char * getName();
	virtual ~Entity(){}

	std::vector<Component *> components;
	glm::mat4 getWorldTransform();
	glm::mat4 localTrans;

	MatrixInfo * getTrans();
	RenderableComponent * getRenderable();
	ScriptComponent * getScript();

	void addComponent(Component * toAdd);
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

