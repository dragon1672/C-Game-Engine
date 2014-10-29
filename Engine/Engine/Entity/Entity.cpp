#include "Entity.h"
#include "Component.h"
#include <Engine\TypeDefs.h>
#include <typeinfo.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Systems/CameraManager.h>

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

template<>
RenderableComponent* Entity::addComponent()
{
	return (RenderableComponent*)addComponent(new RenderableComponent());
}
template<>
CameraComponent* Entity::addComponent()
{
	return (CameraComponent*)addComponent(camManager.getNewCam("newCam"));
}

void Entity::removeComponent(Component * toKill) {
	removeComponent(getIndex(toKill)); 
}
void Entity::init()        {
	for(uint i=0; i<components.size(); i++) components[i]->init();
}
void Entity::start()       {
	if(selectorFunction) {
		for(uint i=0; i<components.size(); i++) {
			if(selectorFunction(components[i])) {
				components[i]->start();
			}
		}
	} else {
		for(uint i=0; i<components.size(); i++) {
			components[i]->start();
		}
	}
}
void Entity::earlyUpdate() {
	if(selectorFunction) {
		for(uint i=0; i<components.size(); i++) {
			if(selectorFunction(components[i])) {
				components[i]->earlyUpdate();
			}
		}
	} else {
		for(uint i=0; i<components.size(); i++) {
			components[i]->earlyUpdate();
		}
	}
}
void Entity::update()      {
	if(selectorFunction) {
		for(uint i=0; i<components.size(); i++) {
			if(selectorFunction(components[i])) {
			components[i]->update();     
			}
		}
	} else {
		for(uint i=0; i<components.size(); i++) {
			components[i]->update();     
		}
	}
}
void Entity::lateUpdate()  {
	if(selectorFunction) {
		for(uint i=0; i<components.size(); i++) {
			if(selectorFunction(components[i])) {
				components[i]->lateUpdate(); 
			}
		}
	} else {
		for(uint i=0; i<components.size(); i++) {
			components[i]->lateUpdate(); 
		}
	}
}

int Entity::getIndex(Component * toFind) const {
	for(uint i=0;i<components.size();i++) {
		if(components[i] == toFind) return i;
	}
	return -1;
}
int Entity::getIndexFromClassName(const char * toFind) const {
	std::string toCheck(toFind);
	for(uint i=0;i<components.size();i++) {
		if(toCheck.compare(std::string(typeid(*components[i]).name()))==0) return i;
	}
	return -1;
}
int Entity::getIndex(const char * toFind) const
{
	std::string toCheck = std::string("class ").append(std::string(toFind));
	for(uint i=0;i<components.size();i++) {
		if(toCheck.compare(std::string(typeid(*components[i]).name()))==0) return i;
	}
	return -1;
}

int Entity::getIndex(std::string toFind) const 
{
	return getIndex(toFind.c_str());
}

glm::mat4 Entity::getWorldTransform()
{
	glm::mat4 ret;
	if(parent != nullptr) ret = parent->getWorldTransform();
	return ret * localTrans.getCompleteTransform();
}

const char * Entity::Name() const
{
	return Object::Name(); // stupid Lua
}

Entity::Entity(const char * name/*="New Game Object"*/, GameObjectManager * manager, Entity * p /*= nullptr*/)  : manager(manager), parent(nullptr), active(true) { this->name = name; Parent(p); }


MatrixInfo * Entity::getTrans() { return &localTrans; }

RenderableComponent * Entity::getRenderable() { return getComponent<RenderableComponent>(); }

ScriptComponent * Entity::getScript() { return getComponent<ScriptComponent>(); }

Entity * Entity::Parent()
{
	return parent;
}

void Entity::Parent(Entity * newGuy)
{
	Entity * old = parent;
	if(Collections::contains(getAllChildren(),newGuy)) {
		throw std::invalid_argument("Recursive children detected");
	}
	if(parent != nullptr) parent->children.erase(this);
	if(newGuy != nullptr) newGuy->children.emplace(this);
	parent = newGuy;
	for (uint i = 0; i < parentChangedEvent.size(); i++) parentChangedEvent[i](old,parent);
}

std::unordered_set<Entity *> Entity::getAllChildren()
{
	std::unordered_set<Entity *> ret = children;
	for (auto var : children)
		for (auto toAdd : var->getAllChildren())
			ret.emplace(toAdd);
	return ret;
}

std::unordered_set<Entity *> Entity::Children()
{
	return children;
}

bool Entity::ComponentsAreReady()
{
	for (uint i = 0; i < components.size(); i++)
	{
		if(!components[i]->isValid())
			return false;
	}
	return true;
}

std::vector<int> Entity::getAllFromClassName(const char * toFind) const 
{
	std::vector<int> ret;
	std::string toCheck(toFind);
	for(uint i=0;i<components.size();i++) {
		if(toCheck.compare(std::string(typeid(*components[i]).name()))==0) ret.push_back(i);
	}
	return ret;
}

std::function<bool(Component*)> Entity::SelectorFunction() const
{
	return selectorFunction;
}

void Entity::SelectorFunction(std::function<bool(Component*)> val)
{
	selectorFunction = val;
}
