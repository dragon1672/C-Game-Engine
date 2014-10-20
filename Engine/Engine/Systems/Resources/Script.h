#pragma once

#include <ExportHeader.h>
#include <string>
#include <Engine\Systems\Resource.h>
#include <luacppinterface.h>

class ENGINE_SHARED	Script : public Resource {
private:
	LuaTable * context;
public:
	Script();
	std::string src;
	LuaTable& getContext();
	void callFunction(std::string methodName);
};