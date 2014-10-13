#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Engine\Tools\MatrixInfo.h>
#include <ExportHeader.h>
#pragma warning( disable : 4244 )
#include <luacppinterface.h>

class Component;

class ENGINE_SHARED Entity {
private:
	const char * name;
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

	//default components getters
	MatrixInfo * getTrans();

	void addComponent(Component * toAdd);
	template<typename T> void removeComponent() {
		removeComponent(getIndex<T>()); 
	}
	template<class T> T* getComponent(std::string name) {
		int index = getIndex(name);
		return (index < 0) ? (T*)components[index] : nullptr;
	}
	template<class T> T* getComponent() {
		int index = getIndex<T>();
		return (index < 0) ? (T*)components[index] : nullptr;
	}
	void removeComponent(Component * toKill);
	void init();
	void earlyUpdate();
	void update();
	void lateUpdate();
};
