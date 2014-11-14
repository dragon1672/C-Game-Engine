#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <ExportHeader.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ObjectManager.h>
#include <unordered_set>

#include <Engine/Tools/MatrixInfo.h>
#include <Engine/Entity/Components/ScriptComponent.h>
#include <Engine/IO/Stream.h>

class RenderableComponent;
class GameObjectManager;
class Component;
class CameraComponent;
class GameObjectManager;

class ENGINE_SHARED Entity : public Object, public StreamableObject {
private:
	void removeComponent_NOW(int toKill);
	void removeComponent(int toKill);
	template<typename T> int getIndex() const {
		return getIndexFromClassName(typeid(T).name());
	}
	int getIndex(Component * toFind) const;
	int getIndex(const char * toFind) const;
	int getIndexFromClassName(const char * toFind) const;
	int getIndex(std::string toFind) const;
	std::vector<int> getAllFromClassName(const char * toFind) const;
	template<typename T> std::vector<int> getAllIndexs() const {
		return getAllFromClassName(typeid(T).name());
	}
	LUA_OBJECT(Entity);

	GameObjectManager * gm;
	double parent;
	Component* addComponent(Component * toAdd);
	std::unordered_set<double> children;
	std::function<bool(Component*)> selectorFunction;

	void resetChildren();
	friend GameObjectManager;


	Stream tmpStream;
public:
	std::function<bool(Component*)> SelectorFunction() const;
	void SelectorFunction(std::function<bool(Component*)> val);
	std::unordered_set<double> Children();
	std::vector<std::function<void(Entity*me)>> StageChanged;
	Entity * Parent();
	void Parent(Entity * newGuy);
	void Parent(double newGuy);
	bool active;


	Entity(std::string name="New Game Object", GameObjectManager * gm = nullptr);
	std::string Name() const;
	void Name(const std::string newName);
	virtual ~Entity();

	std::vector<Component *> components;
	glm::mat4 getWorldTransform();
	MatrixInfo localTrans;
	MatrixInfo * getTrans();
	RenderableComponent * getRenderable();
	ScriptComponent * getScript(std::string name="");
	LuaTable getScriptLua(std::string name="");

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
		if(selectorFunction)
			tmp = Collections::Where<int>(tmp,[this](int&index){ return components[index]->active && selectorFunction(components[index]); });
		return Collections::Select<int,T*>(tmp,[this](int index) {return (T*)components[index];} );
	}
	std::vector<Component *> getAllComponents();

	template<> RenderableComponent* addComponent();
	template<> CameraComponent* addComponent();
	void removeComponent(Component * toKill);
	void init();
	void start(); // called after openGL, every time scene loads, before update
	void earlyUpdate();
	void update();
	void lateUpdate();

	bool ComponentsAreReady();
	std::vector<std::string> getErrors();

	LUA_GET_FUN_PTR(Entity,Parent);
	LUA_GET_FUN_PTR(MatrixInfo,getTrans);

	inline operator LuaUserdata<Entity>() {
		MAKE_LUA_INSTANCE_RET(Entity,ret);

		LUA_BIND_FUN(Entity,ret,Parent);
		LUA_BIND_FUN(Entity,ret,getTrans);
		ret.Bind("GetScript",&Entity::getScriptLua);

		return ret;
	}
	void saveValues(bool useSelector = true);
	void restoreValues(bool useSelector = true);

	virtual void Save(Stream&s);

	virtual void Load(Stream&s);

};

