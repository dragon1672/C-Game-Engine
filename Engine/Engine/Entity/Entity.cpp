#include "Entity.h"
#include "Component.h"
#include <Engine\TypeDefs.h>
#include <typeinfo.h>

void Entity::removeComponent(int toKill) {
	if(toKill >= 0 && toKill < (int)components.size()) {
		Component * c = components[toKill];
		delete(c);
		components.erase(components.begin() + toKill);
	}
}
Component* Entity::addComponent(Component * toAdd) {
	toAdd->parent = this;
	components.push_back(toAdd);
	return toAdd;
}
void Entity::removeComponent(Component * toKill) {
	removeComponent(getIndex(toKill)); 
}
void Entity::init()        {
	auto& t = components.at(0);
	(void)t;
	for(uint i=0; i<components.size(); i++) components[i]->init();
}
void Entity::start()       { for(uint i=0; i<components.size(); i++) components[i]->start();       }
void Entity::earlyUpdate() { for(uint i=0; i<components.size(); i++) components[i]->earlyUpdate(); }
void Entity::update()      { for(uint i=0; i<components.size(); i++) components[i]->update();      }
void Entity::lateUpdate()  { for(uint i=0; i<components.size(); i++) components[i]->lateUpdate();  }

int Entity::getIndex(Component * toFind) {
	for(uint i=0;i<components.size();i++) {
		if(components[i] == toFind) return i;
	}
	return -1;
}

int Entity::getIndex(const char * toFind)
{
	std::string toCheck = std::string("class ").append(std::string(toFind));
	for(uint i=0;i<components.size();i++) {
		if(toCheck.compare(typeid(*components[i]).name())) return i;
	}
	return -1;
}

int Entity::getIndex(std::string toFind)
{
	return getIndex(toFind.c_str());
}

glm::mat4 Entity::getWorldTransform()
{
	glm::mat4 ret;
	Entity * current = this;
	while(current != nullptr) {
		ret = current->localTrans * ret;
		current = current->parent;
	}
	return ret;
}

const char * Entity::getName()
{
	return Object::getName(); // stupid Lua
}

Entity::Entity(const char * name/*="New Game Object"*/, Entity * p /*= nullptr*/)  : parent(p) { this->name = name; }


MatrixInfo * Entity::getTrans() { return getComponent<MatrixInfo>(); }

RenderableComponent * Entity::getRenderable() { return getComponent<RenderableComponent>(); }

ScriptComponent * Entity::getScript() { return getComponent<ScriptComponent>(); }
