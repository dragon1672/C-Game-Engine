#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Engine\Tools\MatrixInfo.h>

class Component;

class Entity {
private:
	void removeComponent(int toKill);
	template<typename T> int getIndex();
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
	template<typename T> void removeComponent();
	template<typename T> T* getComponent();
	void removeComponent(Component * toKill);
	void init();
	void earlyUpdate();
	void update();
	void lateUpdate();
};
