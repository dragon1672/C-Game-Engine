#pragma once

#include <Engine/Defines/LuaVersion.h>
#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>

#define LUA_INSTANCE MasterLua::getInstance().lua

class ENGINE_SHARED MasterLua {
	DEFINE_SINGLETON(MasterLua);
public:
	static const std::string ComponentBaseClass; /* = "ScriptComponent"; */
	Lua lua;
	MasterLua();
	void init();
	static void runLua(std::string toRun);
};