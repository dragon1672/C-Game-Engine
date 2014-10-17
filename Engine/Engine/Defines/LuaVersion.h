#pragma once

#include <luacppinterface.h>
#include <Engine/Tools/MasterLua.h>

//assumes access to Lua lua
#define MAKE_LUA_INSTANCE_RET(class_name,varname) LuaUserdata<class_name> varname = lua.CreateUserdata<class_name>((##class_name##*)this,[](class_name*){}) //this disables the destructor call

#define GET_LUA_VER_PTR(var_type,real_var) LuaUserdata<var_type>get_lua_##real_var##() { return (LuaUserdata<var_type>)(*real_var); }
#define GET_LUA_VER(var_type,real_var) LuaUserdata<var_type>get_lua_##real_var##() { return (LuaUserdata<var_type>)real_var; }
#define BIND_LUA_VER(class_name,var_name,real_var) var_name.Bind(#real_var,  &##class_name##::get_lua_##real_var  )