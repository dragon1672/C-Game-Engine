#pragma once

#include <Engine/Defines/LuaVersion.h>
#include <Engine/Defines/SingletonsDefine.h>

#define LUA_INSTANCE ((Lua)MasterLua::getInstance())

class MasterLua {
	Lua lua;
public:
	MasterLua();
	void init();
	inline operator Lua&() { return lua; }
	DEFINE_SINGLETON(MasterLua);
};