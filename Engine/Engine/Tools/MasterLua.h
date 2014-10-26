#pragma once

#include <Engine/Defines/LuaVersion.h>
#include <Engine/Defines/SingletonsDefine.h>

#define LUA_INSTANCE MasterLua::getInstance().lua

class MasterLua {
public:
	Lua lua;
	MasterLua();
	void init();
	DEFINE_SINGLETON(MasterLua);
};