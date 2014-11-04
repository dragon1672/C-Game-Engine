#include "Entity.h"
#include "Component.h"
#include <Engine\TypeDefs.h>
#include <typeinfo.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Entity/Components/RenderableComponent.h>
#include <Engine/Systems/CameraManager.h>
#include <Engine/Defines/Vectors.h>

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
	if(parent != nullptr) ret = parent->getWorldTransform();
	return ret * localTrans.getCompleteTransform();
}

std::string Entity::Name() const
{
	return name; // stupid Lua
}

void Entity::Name(const std::string newName)
{
	this->name = newName;
	if(newName != name) for (uint i = 0; i < StageChanged.size(); i++) StageChanged[i](this);
}

Entity::Entity(std::string name/*="New Game Object"*/, Entity * p /*= nullptr*/)  : parent(nullptr), active(true) { this->name = name; Parent(p); LUA_OBJECT_START(Entity); }


MatrixInfo * Entity::getTrans() { return &localTrans; }

RenderableComponent * Entity::getRenderable() { return getComponent<RenderableComponent>(); }

ScriptComponent * Entity::getScript(std::string name) {
	auto allScripts = getComponents<ScriptComponent>();
	return Collections::First<ScriptComponent*>(allScripts,[&name](ScriptComponent * toCheck) { return toCheck->getScriptName() == name || name == ""; });
}

Entity * Entity::Parent()
{
	return parent;
}

void Entity::Parent(Entity * newGuy)
{
	//Entity * old = parent;
	if(Collections::contains(getAllChildren(),newGuy)) {
		throw std::invalid_argument("Recursive children detected");
	}
	if(parent != nullptr) parent->children.erase(this);
	if(newGuy != nullptr) newGuy->children.emplace(this);
	parent = newGuy;
	for (uint i = 0; i < StageChanged.size(); i++) StageChanged[i](this);
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

void Entity::saveValues(bool useSelector)
{
	getTrans()->saveValues();
	for (uint i = 0; i < components.size(); i++) {
		if(components[i]->active && (!selectorFunction || !useSelector || selectorFunction && selectorFunction(components[i]))) components[i]->saveValues();
	}
}

void Entity::restoreValues(bool useSelector)
{
	getTrans()->restoreValues();
	for (uint i = 0; i < components.size(); i++) {
		if(components[i]->active && (!selectorFunction || !useSelector || selectorFunction && selectorFunction(components[i]))) components[i]->restoreValues();
	}
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
