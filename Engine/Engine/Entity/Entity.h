#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Engine\Tools\MatrixInfo.h>
#include <ExportHeader.h>

class Component;

class ENGINE_SHARED Entity {
private:
	void removeComponent(int toKill);
	template<typename T> int getIndex() {
		for(uint i=0;i<components.size();i++) {
			if(typeid(*components[i]) == typeid(T)) return i;
		}
		return -1;
	}
	int getIndex(Component * toFind);
public:
	virtual ~Entity(){}

	Entity * parent;
	std::vector<Component *> components;
	MatrixInfo transform;

	Entity(Entity * p = nullptr) {
		parent = p;
	}
	void addComponent(Component * toAdd);
	template<typename T> void removeComponent() {
		removeComponent(getIndex<T>()); 
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
