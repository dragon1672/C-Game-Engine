#include "MasterLua.h"
#include <string>
#include <iostream>
IMPLEMENT_SINGLETON_CAST(MasterLua,Lua);

namespace {

	Lua LoadLua() {
		Lua lua;
		lua.LoadStandardLibraries();

		lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function
		//register all singletons here


		return lua;
	}
MasterLua::MasterLua()
{
	lua.LoadStandardLibraries();

	lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function
	//register all singletons here
}

Lua lua = LoadLua();