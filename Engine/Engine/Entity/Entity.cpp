#include "Entity.h"
#include "Component.h"
#include <Engine\TypeDefs.h>
#include <typeinfo.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Systems/CameraManager.h>
#include <Engine/Defines/Vectors.h>
#include <Engine/IO/Stream.h>
#include <Engine/Systems/GameObjectManager.h>

//events
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ComponentAddedEvent.h>
#include <Engine/Systems/Events/Events/ComponentRemovedEvent.h>
#include <Engine/Systems/Events/Events/EntityParentChangedEvent.h>

void Entity::removeComponent(int toKill) {
	if(toKill >= 0 && toKill < (int)components.size()) {
		Component * c = components[toKill];
		components.erase(components.begin() + toKill);
		ComponentRemovedEvent data(this,c);
		emitEvent(data);
		delete(c);
	}
}
Component* Entity::addComponent(Component * toAdd) {
	toAdd->parent = this;
	components.push_back(toAdd);
	ComponentAddedEvent data(this,toAdd);
	emitEvent(data);
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
	for(uint i=0; i<components.size(); i++) {
		if(components[i]->active) {
			components[i]->start();
		}
	}
}
void Entity::earlyUpdate() {
	for(uint i=0; i<components.size(); i++) {
		if(components[i]->active && (!selectorFunction || selectorFunction && selectorFunction(components[i]))) {
			components[i]->earlyUpdate();
		}
	}
}
void Entity::update()      {
	for(uint i=0; i<components.size(); i++) {
		if(components[i]->active && (!selectorFunction || selectorFunction && selectorFunction(components[i]))) {
			components[i]->update();     
		}
	}
}
void Entity::lateUpdate()  {
	for(uint i=0; i<components.size(); i++) {
		if(components[i]->active && (!selectorFunction || selectorFunction && selectorFunction(components[i]))) {
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
	if(Parent() != nullptr) ret = Parent()->getWorldTransform();
	return ret * localTrans.getCompleteTransform();
}

std::string Entity::Name() const
{
	return Object::Name(); // stupid Lua
}

void Entity::Name(const std::string newName)
{
	Object::Name(newName);
	if(newName != Name()) for (uint i = 0; i < StageChanged.size(); i++) StageChanged[i](this);
}


MatrixInfo * Entity::getTrans() { return &localTrans; }

RenderableComponent * Entity::getRenderable() { return getComponent<RenderableComponent>(); }

ScriptComponent * Entity::getScript(std::string name) {
	auto allScripts = getComponents<ScriptComponent>();
	return Collections::First<ScriptComponent*>(allScripts,[&name](ScriptComponent * toCheck) { return toCheck->getScriptName() == name || name == ""; });
}

Entity * Entity::Parent()
{
	return gm->getEntity(parent);
}

void Entity::Parent(double newGuy)
{
	Parent(gm->getEntity(newGuy));
}

void Entity::Parent(Entity * newGuy)
{
	Entity * old = Parent();
	if(newGuy != nullptr && Collections::contains(children,newGuy->getID())) {
		throw std::invalid_argument("Recursive children detected");
	}
	if(old    != nullptr) old->children.erase(getID());
	if(newGuy != nullptr) newGuy->children.emplace(getID());
	parent = newGuy != nullptr ? newGuy->getID() : Object::NULL_OBJECT_ID();
	EntityParentChangedEvent data(this,old,newGuy);
	emitEvent(data);
	for (uint i = 0; i < StageChanged.size(); i++) StageChanged[i](this);
}


std::unordered_set<double> Entity::Children()
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

std::vector<Component *> Entity::getAllComponents()
{
	return components;
}

Entity::~Entity()
{
	DELETE_VECTOR(components);
	LUA_OBJECT_END(Entity);
}

LuaTable Entity::getScriptLua(std::string name)
{
	auto ret = getScript(name);
	if(ret != nullptr) return ret->getContext();
	return LUA_INSTANCE.CreateTable();
}

std::vector<std::string> Entity::getErrors()
{
	std::vector<std::string> ret;
	for (uint i = 0; i < components.size(); i++) { Collections::AddToFirstVector(ret,components[i]->getErrors()); }
	return ret;
}

void Entity::Save(Stream&s)
{
	Object::ObjectSave(s);
	s << parent << active << components << getTrans();
}

void Entity::Load(Stream&s)
{
	Object::ObjectLoad(s);
	s >> parent >> active >> components >> getTrans();
}

Entity::Entity(std::string name/*="New Game Object"*/, GameObjectManager * gm /*= nullptr*/) : parent(Object::NULL_OBJECT_ID()), gm(gm), active(true), Object(name)
{
	LUA_OBJECT_START(Entity);
}

void Entity::resetChildren()
{
	children.clear();
}
