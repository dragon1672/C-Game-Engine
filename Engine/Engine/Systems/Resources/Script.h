#pragma once

#include <ExportHeader.h>
#include <string>
#include <Engine\Systems\Resource.h>

class ENGINE_SHARED	Script : public Resource {
public:
	Script() {}
	Script(std::string name) { this->name = name; }
	std::string src;
	virtual void PassDownToHardWare() {}
};