#pragma once

#include <vector>
#include <Engine/Systems/Object.h>
#include <ExportHeader.h>


class ObjectManagerPrivates;
class ENGINE_SHARED ObjectManager {
private:
	ObjectManagerPrivates * privates;
	bool removeName(std::string name, Object * ptr);
	bool removeId(double id);
	void addName(std::string name, Object * ptr);
	void addId(double id, Object * ptr);
public:
	ObjectManager();
	~ObjectManager();
	void Register(Object& toAdd);
	void Register(Object * toAdd);
	void Register(std::vector<Object *> toAdd);
	void UnRegister(Object& toKill);
	void UnRegister(Object * toKill);
	Object * getFirst(double id) const;
	Object * getFirst(const char * name) const;
	std::vector<Object *> getAll(const char * name) const;
	std::vector<Object *> getAll() const;
	void ClearAll();
	bool Contains(Object *o);
};