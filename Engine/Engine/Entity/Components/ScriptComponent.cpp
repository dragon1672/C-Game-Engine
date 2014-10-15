#include "ScriptComponent.h"
#include <luacppinterface.h>

Lua LoadLua() {
	Lua ret;
	ret.LoadStandardLibraries();
	return ret;
}
Lua ScriptComponent::lua = LoadLua();

const char * ScriptComponent::LuaTemplate = ""
	"context = {}                                            \n"
	"context.exampleVar = 5;                                 \n"
	"	                                                     \n"
	"--Fill Me and init variables                            \n"
	"--Called before any update function on game start       \n"
	"context.start = function()                              \n"
	"	content.exampleVar = 20;                             \n"
	"	                                                     \n"
	"	return true -- never edit                            \n"
	"end                                                     \n"
	"	                                                     \n"
	"	                                                     \n"
	"--Called before update                                  \n"
	"context.earlyUpdate = function()                        \n"
	"	context.exampleVar = context.exampleVar+ 1;          \n"
	"	                                                     \n"
	"	return true -- never edit                            \n"
	"end                                                     \n"
	"	                                                     \n"
	"	                                                     \n"
	"context.update = function()                             \n"
	"	print(context.exampleVar)                            \n"
	"	                                                     \n"
	"	return true -- never edit                            \n"
	"end                                                     \n"
	"	                                                     \n"
	"	                                                     \n"
	"--called after all other updates                        \n"
	"context.lateUpdate = function()                         \n"
	"	                                                     \n"
	"	return true -- never edit                            \n"
	"end                                                     \n"
	"";

void ScriptComponent::init() {
	context = lua.GetGlobalEnvironment().Get<LuaTable>("context");
	auto start = context.Get<LuaFunction<bool()>>("start");
	start.Invoke();
}
void ScriptComponent::earlyUpdate() {
	static LuaFunction<bool()> leFunc = context.Get<LuaFunction<bool()>>("earlyUpdate"); // run once and done :D
	leFunc.Invoke();
}
void ScriptComponent::update() {
	static LuaFunction<bool()> leFunc = context.Get<LuaFunction<bool()>>("update"); // run once and done :D
	leFunc.Invoke();
}

void ScriptComponent::lateUpdate() {
	static LuaFunction<bool()> leFunc = context.Get<LuaFunction<bool()>>("lateUpdate"); // run once and done :D
	leFunc.Invoke();
}

ScriptComponent::ScriptComponent() : context(nullptr,-1) { }