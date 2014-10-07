#pragma once

#include <Engine\Entity\Entity.h>

class Component { 
protected:
	friend Entity;
	Entity * parent;
public:
	virtual void init()        {}
	virtual void earlyUpdate() {}
	virtual void update()      {}
	virtual void lateUpdate()  {}
};