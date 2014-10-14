#include "ScriptComponent.h"
#include <luacppinterface.h>

Lua LoadLua() {
	Lua ret;
	ret.LoadStandardLibraries();
	return ret;
}
Lua ScriptComponent::lua = LoadLua();

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