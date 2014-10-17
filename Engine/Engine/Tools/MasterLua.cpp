#include "MasterLua.h"
#include <string>
#include <iostream>

namespace {

	Lua LoadLua() {
		Lua lua;
		lua.LoadStandardLibraries();

		lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function
		//register all singletons here


		return lua;
	}

}

Lua lua = LoadLua();