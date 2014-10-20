#include "MasterLua.h"
#include <string>
#include <iostream>

//singletons
#include <Engine/Tools/Timer.h>
#include <engine/Tools/Random/MyRandom.h>
#include <Engine/Tools/Random/StringRandom.h>


IMPLEMENT_SINGLETON(MasterLua);

MasterLua::MasterLua()
{
	lua.LoadStandardLibraries();

	lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function

	//load class def
	lua.RunScript("function class(a,b)local c={}if not b and type(a)=='function'then b=a;a=nil elseif type(a)=='table'then for d,e in pairs(a)do c[d]=e end;c._base=a end;"
		"c.__index=c;local f={}f.__call=function(g,...)local h={}setmetatable(h,c)if b then b(h,...)else if a and a.init then a.init(h,...)end end;return h end;c.init=b;"
		"c.is_a=function(i,j)local k=getmetatable(i)while k do if k==j then return true end;k=k._base end;return false end;setmetatable(c,f)return c end");

	//random
	auto rand = lua.CreateTable();

	rand.Set("float",     lua.CreateFunction<float()>([]() { return Random::Float(); }));
	rand.Set("bool",      lua.CreateFunction<bool()>([]() { return Random::Bool(); }));
	rand.Set("RangeFloat",lua.CreateFunction<float(float,float)>([](float low, float high) { return Random::Float(low,high); }));
	rand.Set("RangeInt",  lua.CreateFunction<int(int,int)>([](int low, int high) { return Random::Int(low,high); }));
	LuaTable randStr = lua.CreateTable();
	rand.Set("String",    randStr);
	randStr.Set("String",    lua.CreateFunction<std::string(int,int,int)>([](int len, int start, int end) { return Random::rString::makeString(len, start, end); }));
	randStr.Set("Letters",   lua.CreateFunction<std::string(int)>([](int len) { return Random::rString::Letters(len); }));
	randStr.Set("UppercaseLetters",   lua.CreateFunction<std::string(int)>([](int len) { return Random::rString::UppercaseLetters(len); }));
	randStr.Set("LowercaseLetters",   lua.CreateFunction<std::string(int)>([](int len) { return Random::rString::LowercaseLetters(len); }));
	lua.GetGlobalEnvironment().Set("Random",rand);
}

void MasterLua::init()
{
	//register all singletons here
	auto global = lua.GetGlobalEnvironment();
	global.Set("Timer",(LuaUserdata<Timer>)Timer::getInstance());
}
