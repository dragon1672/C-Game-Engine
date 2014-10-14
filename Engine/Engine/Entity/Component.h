#pragma once

#include <ExportHeader.h>

class Entity;
class ENGINE_SHARED Component { 
protected:
	friend Entity;
	Entity * parent;
public:
	virtual void init()        {}
	virtual void earlyUpdate() {}
	virtual void update()      {}
	virtual void lateUpdate()  {}
	//virtual LuaTable * getLuaComponent() = 0;
};