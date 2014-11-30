#include "ObjectManager.h"
#include <unordered_set>
#include <map>
#include <vector>
#include <Engine/TypeDefs.h>
#include <Engine/Tools/Printer.h>
#include <cassert>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ObjectChangedNameEvent.h>
#include <Engine/Systems/Events/Events/ObjectChangeIDEvent.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Defines/Vectors.h>


class ObjectManagerPrivates {
public:
	struct ObjectMatches : public std::vector<Object*> { public: operator std::vector<Object*>() { return *this; }};
	std::map<std::string,ObjectMatches> nameMap;
	std::map<double,Object *> idMap;
	bool ContainsId  (Object * toCheck)  { return Contains(toCheck->getID());   }
	bool ContainsName(Object * toCheck)  { return Contains(toCheck->Name()); }
	bool Contains(double toCheck)       { return idMap.find(toCheck) != idMap.end();   }
	bool Contains(std::string name)  { return nameMap.find(name)  != nameMap.end(); }
};

ObjectManager::ObjectManager() : privates(nullptr)
{
	SAFE_NEW(privates,ObjectManagerPrivates());
	eventManager.Subscribe<ObjectChangedNameEvent>([this](EventData*d,Object*o){
		if(o==nullptr) return;
		ObjectChangedNameEvent * data = (ObjectChangedNameEvent*)d;
		if(!privates->Contains(data->oldName)) return;
		if(removeName(data->oldName,o)) {
			addName(data->newName,o);
		}
	});
	eventManager.Subscribe<ObjectChangeIDEvent>([this](EventData*d,Object*o){
		if(o==nullptr) return;
		ObjectChangeIDEvent * data = (ObjectChangeIDEvent*)d;
		if(!privates->Contains(data->old)) return;
		if(removeId(data->old)) {
			addId(data->n,o);
		}
	});
	eventManager.Subscribe<EntityRemovedEvent>([this](EventData*d,Object*o){
		EntityRemovedEvent * data = (EntityRemovedEvent*)d;
		UnRegister(data->entity);
	});
}

ObjectManager::~ObjectManager()
{
	SAFE_DELETE(privates);
}

void ObjectManager::Register(Object& toAdd) {
	Register(&toAdd);
}
void ObjectManager::Register(Object * toAdd)
{
	if(toAdd == nullptr) return;
	addId(toAdd->getID(),toAdd);

	addName(toAdd->Name(),toAdd);
}

void ObjectManager::Register(std::vector<Object *> toAdd)
{
	for (uint i = 0; i < toAdd.size(); i++) {
		Register(toAdd[i]);
	}
}

void ObjectManager::UnRegister(Object& toKill) {
	UnRegister(&toKill);
}
void ObjectManager::UnRegister(Object * toKill)
{
	if(toKill == nullptr) return;
	removeId(toKill->getID());
	
	removeName(toKill->Name(),toKill);
}

Object * ObjectManager::getFirst(double id) const
{
	return privates->Contains(id) ? privates->idMap[id] : nullptr;
}

Object * ObjectManager::getFirst(const char * name) const
{
	return privates->Contains(name) ? privates->nameMap[name][0] : nullptr;
}

std::vector<Object *> ObjectManager::getAll() const
{
	std::vector<Object *> ret;
	for(auto i : privates->idMap) {
		ret.push_back(i.second);
	}
	return ret;
}
std::vector<Object *> ObjectManager::getAll(const char * name) const
{
	return privates->Contains(name) ? privates->nameMap[name] : std::vector<Object*>();
}

void ObjectManager::ClearAll()
{
	SAFE_NEW(privates,ObjectManagerPrivates());
}

bool ObjectManager::Contains(Object *o)
{
	return privates->ContainsId(o);
}

bool ObjectManager::removeId(double id)
{
	if(privates->Contains(id)) {
		privates->idMap.erase(id);
		return true;
	}
	return false;
}

bool ObjectManager::removeName(std::string name, Object * ptr)
{
	if(!privates->Contains(name))// not in map
		return false;

	auto& data = privates->nameMap[name];
	int oldSize = data.size();
	VECTOR_REMOVE_CONDITION(data, == ptr);
	int newSize = data.size();
	if(data.size() <= 0) {
		privates->nameMap.erase(name);
	}
	return oldSize != newSize; // return if something got removed
}

void ObjectManager::addName(std::string name, Object * ptr)
{
	if(!privates->Contains(name)) { // not in map
		privates->nameMap.emplace(name,ObjectManagerPrivates::ObjectMatches());
	}
	privates->nameMap[name].push_back(ptr);
}

void ObjectManager::addId(double id, Object * ptr)
{
	if(privates->Contains(id)) {
		printer.LogError("Object with same ID already exists in object manager");
		assert(false);
	}
	privates->idMap.emplace(id,ptr);
}
