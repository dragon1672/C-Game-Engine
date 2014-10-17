#pragma once

#include <Engine/Defines/LuaVersion.h>
#include <Engine/Defines/SingletonsDefine.h>

#define LUA_INSTANCE MasterLua::getInstance()

class MasterLua {
	Lua lua;
public:
	MasterLua();
	DEFINE_SINGLETON_CAST(MasterLua,Lua);
	inline operator Lua&() { return lua; }
};