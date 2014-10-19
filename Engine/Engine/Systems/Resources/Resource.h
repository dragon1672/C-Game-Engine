#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Object.h>

class ENGINE_SHARED Resource : public Object {
public:
	virtual void PassDownToHardWare() = 0;
	virtual void init() {};
	virtual void update() {}
};