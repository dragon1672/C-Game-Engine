#include "ObjectManager.h"
#include <unordered_set>
#include <map>
#include <vector>
#include <Engine/TypeDefs.h>
#include <Engine/Tools/Printer.h>
#include <cassert>

class ObjectManagerPrivates {
public:
	uint GlobalId;
	struct ObjectMatches : public std::vector<Object*> { public: operator std::vector<Object*>() { return *this; }};
	std::map<const char *,ObjectMatches> nameMap;
	std::map<int,Object *> idMap;
	bool ContainsId  (Object * toCheck)  { return Contains(toCheck->getID());   }
	bool ContainsName(Object * toCheck)  { return Contains(toCheck->Name()); }
	bool Contains(int toCheck)       { return idMap.find(toCheck) != idMap.end();   }
	bool Contains(const char * name) { return nameMap.find(name)  != nameMap.end(); }
	ObjectManagerPrivates() : GlobalId(0) {}
};

ObjectManager::ObjectManager()
{
	privates = new ObjectManagerPrivates();
}

ObjectManager::~ObjectManager()
{
	delete privates;
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
	privates->idMap[toAdd->getID()] = toAdd;

	if(!privates->ContainsName(toAdd)) { // not in map
		privates->nameMap.emplace(toAdd->Name(),ObjectManagerPrivates::ObjectMatches());
	}
	privates->nameMap[toAdd->Name()].push_back(toAdd);
}

void ObjectManager::UnRegister(Object& toKill) {
	UnRegister(&toKill);
}
void ObjectManager::UnRegister(Object * toKill)
{
	if(!privates->ContainsId(toKill))
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

Object * ObjectManager::getFirst(int id)
{
	return privates->Contains(id) ? privates->idMap[id] : nullptr;
}

Object * ObjectManager::getFirst(const char * name)
{
	return privates->Contains(name) ? privates->nameMap[name][0] : nullptr;
}

std::vector<Object *> ObjectManager::getAll(const char * name)
{
	return privates->Contains(name) ? privates->nameMap[name] : std::vector<Object*>();
}

int ObjectManager::getUniqueId()
{
	return privates->GlobalId++;
}
