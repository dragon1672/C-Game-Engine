#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Object.h>

class Entity;
class ENGINE_SHARED Component : public Object { 
protected:
	friend Entity;
	Entity * parent;
public:
	Component() {}
	Component(const char * name) { this->name = name;}
	inline Entity * Parent() { return parent; }
	virtual void init()        {} // called once
	virtual void start()       {} // called every scene load before update starts
	virtual void earlyUpdate() {}
	virtual void update()      {}
	virtual void lateUpdate()  {}
	virtual bool isValid() = 0;
};