#include "ObjectManager.h"
#include <unordered_set>
#include <map>
#include <vector>
#include <Engine/TypeDefs.h>
#include <Engine/Tools/Printer.h>
#include <cassert>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ObjectChangedNameEvent.h>
#include <Engine/Systems/Events/Events/EntityRemovedEvent.h>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/Entity/Entity.h>


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
		if(!privates->ContainsId(o)) return;
		ObjectChangedNameEvent * data = (ObjectChangedNameEvent*)d;
		removeName(data->oldName,o);
		addName(data->newName,o);
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

void ObjectManager::removeId(double id)
{
	if(privates->Contains(id))
		privates->idMap.erase(id);
}

void ObjectManager::removeName(std::string name, Object * ptr)
{
	if(!privates->Contains(name))// not in map
		return;

	auto& data = privates->nameMap[name];
	for (unsigned int i = 0; i < data.size(); i++) { // loop through matches to remove
		if(data[i] == ptr) {
			data.erase(data.begin() + i);
			i--;
		}
	}
	if(data.size() <= 0) {
		privates->nameMap.erase(name);
	}
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
