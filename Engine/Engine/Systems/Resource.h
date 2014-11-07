#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Object.h>
#include <vector>

class ENGINE_SHARED Resource : public Object {
public:
	Resource(std::string name = "") : Object(name) {}
	virtual void PassDownToHardWare() = 0;
	virtual void init() {};
	virtual void update() {}
	virtual bool isValid() = 0;
	virtual void shutdown() {}
	virtual std::vector<std::string> getErrors() = 0;
};