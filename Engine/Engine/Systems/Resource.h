#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Object.h>
#include <vector>

#include <Engine/IO/StreamableObject.h>

class ENGINE_SHARED Resource : public Object {
public:
	Resource(std::string name = "") : Object(name) {}
	virtual void PassDownToHardWare() = 0;
	virtual void init() {};
	virtual void update() {}
	virtual void shutdown() {}
	virtual bool isValid() = 0;
	virtual std::vector<std::string> getErrors() = 0;
	inline void ObjectSave(Stream& s) {
		Object::ObjectSave(s);
		ChildSave(s);
	}
	inline void ObjectLoad(Stream& s) {
		Object::ObjectLoad(s);
		ChildLoad(s);
	}
	virtual bool equals(Resource& that) const = 0;
	virtual bool equals(Resource* that) const {
		if(this == that) return true;
		return equals(*that);
	}
protected:
	virtual void ChildSave(Stream& s) = 0;
	virtual void ChildLoad(Stream& s) = 0;
};

#define MAKE_RESOURCE_CLASS(name) name : public Resource_CRTP<name>

template<typename Derived>
class Resource_CRTP : public Resource {
public:
	Resource_CRTP(std::string name = "") : Resource(name) {}
	virtual bool equals(Derived& that) const = 0;
	virtual bool equals(Derived * that) const {
		if(this==that) return true;
		return equals(*that);
	}
	virtual bool equals(Resource& that) const {
		if(std::string(typeid(that).name()) != typeid(Derived).name()) return false; // not the same type
		return equals((Derived *)&that); // can 
	}

};