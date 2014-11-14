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
protected:
	virtual void ChildSave(Stream& s) = 0;
	virtual void ChildLoad(Stream& s) = 0;
};