#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Object.h>
#include <Engine/Systems/Resources/Shaders/ShaderObject.h>

class Entity;
class ENGINE_SHARED Component : public Object, public ShaderObject { 
protected:
	friend Entity;
	Entity * parent;
public:
	bool active;
	Component() : active(true) {}
	Component(const char * name) : active(true) { this->name = name;}
	inline Entity * Parent() { return parent; }
	virtual void init()        {} // called once
	virtual void start()       {} // called every scene load before update starts
	virtual void earlyUpdate() {}
	virtual void update()      {}
	virtual void lateUpdate()  {}
	virtual void saveValues()  {}
	virtual void restoreValues()  {}
	virtual bool isValid() = 0;
};