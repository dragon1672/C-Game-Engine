#pragma once

#include <vector>
#include <Engine/Systems/Object.h>
#include <ExportHeader.h>


class ObjectManagerPrivates;
class ENGINE_SHARED ObjectManager {
private:
	ObjectManagerPrivates * privates;
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
	int getUniqueId();
};