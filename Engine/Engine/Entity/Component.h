#pragma once

#include <ExportHeader.h>

class Entity;
class ENGINE_SHARED Component { 
protected:
	friend Entity;
	Entity * parent;
public:
	virtual void init()        {} // called once
	virtual void start()       {} // called every scene load before update starts
	virtual void earlyUpdate() {}
	virtual void update()      {}
	virtual void lateUpdate()  {}
};