#include "MasterLua.h"
#include <string>
#include <iostream>

//singletons
#include <Engine/Tools/Timer.h>
#include <engine/Tools/Random/MyRandom.h>


IMPLEMENT_SINGLETON(MasterLua);

MasterLua::MasterLua()
{
	lua.LoadStandardLibraries();

	lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function

	//random
	auto rand = lua.CreateTable();

	rand.Set("float",     lua.CreateFunction<float()>([]() { return Random::randomFloat(); }));
	rand.Set("bool",      lua.CreateFunction<bool()>([]() { return Random::randomBool(); }));
	rand.Set("RangeFloat",lua.CreateFunction<float(float,float)>([](float low, float high) { return Random::randomFloat(low,high); }));
	rand.Set("RangeInt",  lua.CreateFunction<int(int,int)>([](int low, int high) { return Random::randomInt(low,high); }));
	lua.GetGlobalEnvironment().Set("Random",rand);
}

void MasterLua::init()
{
	//register all singletons here
	auto global = lua.GetGlobalEnvironment();
	global.Set("Timer",(LuaUserdata<Timer>)Timer::getInstance());
}
