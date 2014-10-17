#include "MasterLua.h"
#include <string>
#include <iostream>


IMPLEMENT_SINGLETON_CAST(MasterLua,Lua);

MasterLua::MasterLua()
{
	lua.LoadStandardLibraries();

	lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function
	//register all singletons here
}