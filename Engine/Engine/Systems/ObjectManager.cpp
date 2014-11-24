#include "ObjectManager.h"
#include <unordered_set>
#include <map>
#include <vector>
#include <Engine/TypeDefs.h>
#include <Engine/Tools/Printer.h>
#include <cassert>

#include <Engine/Systems/Events/EventManager.h>
#include <Engine/Systems/Events/Events/ObjectChangedNameEvent.h>
#include <Engine/Defines/SafeNewAndDelete.h>


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
	eventManager.Subscribe<ObjectChangedNameEvent>([this](EventData*,Object*o){
		if(privates->ContainsName(o)) { // TODO: optimize
			UnRegister(o);
			Register(o);
		}
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
	if(privates->ContainsId(toAdd)) {
		printer.LogError("Object with same ID already exists in object manager");
		assert(false);
	}
	privates->idMap.emplace(toAdd->getID(),toAdd);

	if(!privates->ContainsName(toAdd)) { // not in map
		privates->nameMap.emplace(toAdd->Name(),ObjectManagerPrivates::ObjectMatches());
	}
	privates->nameMap[toAdd->Name()].push_back(toAdd);
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
	if(toKill==nullptr) return;
	if(privates->ContainsId(toKill))
		privates->idMap.erase(toKill->getID());

	if(!privates->ContainsName(toKill))// not in map
		return;

	auto& data = privates->nameMap[toKill->Name()];
	for (unsigned int i = 0; i < data.size(); i++) { // loop through matches to remove
		if(data[i] == toKill) {
			data.erase(data.begin() + i);
			i--;
		}
	}
	if(data.size() <= 0) {
		privates->nameMap.erase(toKill->Name());
	}
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
