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
#include <Engine/DebugTools/DebugMemHeader.h>

//events
#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ComponentAddedEvent.h>
#include <Engine/Systems/Events/Events/ComponentRemovedEvent.h>
#include <Engine/Systems/Events/Events/EntityParentChangedEvent.h>

void Entity::removeComponent(uint toKill) {
	if(toKill >= 0 && toKill < components.size()) {
		Component * c = components[toKill];
		if(toKill == components.size()-1) components.pop_back();
		else components.erase(components.begin() + toKill);
		emitEvent(new ComponentRemovedEvent(this,c));
		delete(c);
	}
}
Component* Entity::addComponent(Component * toAdd) {
	toAdd->parent = this;
	components.push_back(toAdd);
	emitEvent(new ComponentAddedEvent(this,toAdd));
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
		if(components[i]->active) {
			components[i]->earlyUpdate();
		}
	}
}
void Entity::update()      {
	for(uint i=0; i<components.size(); i++) {
		if(components[i]->active) {
			components[i]->update();     
		}
	}
}
void Entity::lateUpdate()  {
	for(uint i=0; i<components.size(); i++) {
		if(components[i]->active) {
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
	return gameManager.getEntity(parent);
}

void Entity::Parent(double newGuy, bool fireEvents)
{
	Parent(gameManager.getEntity(newGuy),fireEvents);
}

void Entity::Parent(Entity * newGuy, bool fireEvents)
{
	Entity * old = Parent();
	if(newGuy != nullptr && Collections::contains(children,newGuy->getID())) {
		throw std::invalid_argument("Recursive children detected");
	}
	if(old    != nullptr) old->children.erase(getID());
	if(newGuy != nullptr) newGuy->children.emplace(getID());
	parent = newGuy != nullptr ? newGuy->getID() : Object::NULL_OBJECT_ID();
	if(fireEvents && newGuy != old) emitEvent(new EntityParentChangedEvent (this,old,newGuy));
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

std::vector<Component *> Entity::getAllComponents()
{
	return components;
}

Entity::~Entity()
{
	shutdown(false);
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
	s << parent << active;
	s << *getTrans();
	s << components.size();
	for (uint i = 0; i < components.size(); i++)
	{
		s << components[i]->Class_Name();
		s << *components[i];
	}
}

void Entity::Load(Stream&s)
{
	shutdown(true);
	Object::ObjectLoad(s);
	s >> parent >> active;
	s >> *getTrans();
	uint size;
	s >> size;
	for (uint i = 0; i < size; i++)
	{
		std::string componentName;
		s >> componentName;
		auto currentComponent = addComponent(Component::GetInstanceFromTypeString(componentName));
		s >> *currentComponent;
	}
}

Entity::Entity(std::string name/*="New Game Object"*/, GameObjectManager * gm /*= nullptr*/) : parent(Object::NULL_OBJECT_ID()), active(true), Object(name), tag(-1)
{
	LUA_OBJECT_START(Entity);
}

void Entity::resetChildren()
{
	children.clear();
}

Entity::operator LuaUserdata<Entity>()
{
	MAKE_LUA_INSTANCE_RET(Entity,ret);

	LUA_BIND_FUN(Entity,ret,Parent);
	LUA_BIND_FUN(Entity,ret,getTrans);
	ret.Bind("GetScript",&Entity::getScriptLua);
	ret.Bind("Broadcast",&Entity::Broadcast);
	ret.Bind("BroadcastInChildren",&Entity::BroadcastInChildren);
	ret.Bind("Active",&Entity::SetActive);
	ret.Bind("Active",&Entity::GetActive);
	ret.Bind("Parent",&Entity::ParentFromLUA);
	ret.Bind("Clone",&Entity::Clone_Lua);
	ret.Bind("getID",&Entity::getID_LUA);

	return ret;
}

void Entity::shutdown(bool fireEvents)
{
	LUA_OBJECT_END(Entity);
	while(fireEvents && components.size()>0)
		removeComponent(components.size()-1);
	DELETE_VECTOR(components); // clean up if fireEvents is false
	Parent(nullptr,fireEvents);
}

void Entity::callLuaMethod(std::string methodName, bool callInChildren)
{
	auto scripts = getComponents<ScriptComponent>();
	for(auto& s : scripts) {
		s->callMethod(methodName);
	}
	if(callInChildren) {
		for(double id : children) {
			gameManager.getEntity(id)->callLuaMethod(methodName,callInChildren);
		}
	}
}

Entity * Entity::Clone(bool cloneChildren)
{
	auto newClonedEntity = gameManager.AddEntity(Name()+"_Clone");
	auto componentsToCopy = this->getAllComponents();
	for (uint i = 0; i < componentsToCopy.size(); i++) {
		auto newInstance = componentsToCopy[i]->getNewInstanceOfCurrentType();
		if(newInstance != nullptr) {
			componentsToCopy[i]->CopyInto(newInstance);
			newClonedEntity->addComponent(newInstance);
		}
	}
	this->getTrans()->CopyInto(newClonedEntity->getTrans());
	newClonedEntity->Parent(this->Parent());
	if(cloneChildren) {
		auto children = this->Children();
		for(auto& eID : children) {
			Entity * e = gameManager.getEntity(eID);
			e->Clone();
			e->Parent(newClonedEntity);
		}
	}
	return newClonedEntity;
}

void Entity::Broadcast(std::string methodName)
{
	callLuaMethod(methodName,false);
}

void Entity::BroadcastInChildren(std::string methodName)
{
	callLuaMethod(methodName,true);
}

void Entity::Tag(std::string val)
{
	tag = gameManager.getTagVal(val);
}

void Entity::SetTag(std::string val)
{
	tag = gameManager.getTagVal(val);
}

void Entity::ParentFromLUA(LuaUserdata<Entity> e)
{
	Parent(e->getID());
}

LuaUserdata<Entity> Entity::Clone_Lua(bool recursive)
{
	return *Clone(recursive);
}
