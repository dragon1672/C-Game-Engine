#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <ExportHeader.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Systems/ObjectManager.h>
#include <unordered_set>

#include <Engine/Tools/MatrixInfo.h>
#include <Engine/Entity/Components/ScriptComponent.h>
#include <Engine/IO/StreamableObject.h>
#include <Engine/Tools/CollectionEditing.h>

class RenderableComponent;
class GameObjectManager;
class Component;
class CameraComponent;
class GameObjectManager;

class ENGINE_SHARED Entity : public Object, public StreamableObject {
private:
	void removeComponent(uint toKill);
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

	int tag;
	double parent;
	Component* addComponent(Component * toAdd);

	std::unordered_set<double> children;
	void resetChildren();

	double getID_LUA() { return getID(); }

	LUA_GET_FUN_PTR(Entity,Parent);
	LUA_GET_FUN_PTR(MatrixInfo,getTrans);
	LuaUserdata<CameraComponent> getCam_LUA();

	bool active;

	friend GameObjectManager;
public:
	std::unordered_set<double> Children();
	std::vector<std::function<void(Entity*me)>> StageChanged;
	Entity * Parent() const;
	void Parent(Entity * newGuy, bool fireEvents = true);
	void Parent(double   newGuy, bool fireEvents = true);

	Entity * GetParent() { return Parent(); }
	void SetParentFromID(double newGuy) { Parent(newGuy); }

	bool GetActive() const;
	void SetActive(bool val);
	int  Tag() const { return tag; }
	void Tag(int val) { tag = val; }
	void Tag(std::string val);
	int  GetTag() const { return tag; }
	void SetTag(int val) { tag = val; }
	void SetTag(std::string val);


	void callLuaMethod(std::string methodName, bool callInChildren);
	void Broadcast(std::string methodName);
	void BroadcastInChildren(std::string methodName);


	Entity(std::string name="New Game Object", GameObjectManager * gm = nullptr);
	std::string Name() const;
	void Name(const std::string newName);
	virtual ~Entity();

	std::vector<Component *> components;
	glm::mat4 getWorldTransform();
	MatrixInfo localTrans;
	MatrixInfo * getTrans();
	CameraComponent * getCam();
	RenderableComponent * getRenderable();
	ScriptComponent * getScript(std::string name="");
	LuaTable getScriptLua(std::string name="");
	bool hasScript(std::string name);

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

	Entity * Clone(bool cloneChildren = true);
	LuaUserdata<Entity> Clone_Lua(bool recursive);

	bool ComponentsAreReady();
	std::vector<std::string> getErrors();

	operator LuaUserdata<Entity>();

	virtual void Save(Stream&s);

	virtual void Load(Stream&s);
	void shutdown(bool fireEvents = true);
};

