#include "ScriptComponent.h"
#include <luacppinterface.h>
#include <iostream>

Lua LoadLua() {
	Lua ret;
	ret.LoadStandardLibraries();

	ret.GetGlobalEnvironment().Set("print",ret.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function

	return ret;
}
Lua ScriptComponent::lua = LoadLua();

const char * ScriptComponent::LuaTemplate = ""
	"context = {}                                          \n"
	"--keep all vars within scope of context               \n"
	"context.exampleVar = 5;                               \n"
	"                                                      \n"
	"--called first                                        \n"
	"context.start = function()                            \n"
	"    print(context.exampleVar)                         \n"
	"    return true                                       \n"
	"end                                                   \n"
	"                                                      \n"
	"--updates are called after start                      \n"
	"context.earlyUpdate = function()                      \n"
	"    context.exampleVar = context.exampleVar + 1;      \n"
	"    return true                                       \n"
	"end                                                   \n"
	"context.update = function()                           \n"
	"    print(context.exampleVar)                         \n"
	"    return true                                       \n"
	"end                                                   \n"
	"context.lateUpdate = function()                       \n"
	"    --yay                                             \n"
	"    return true                                       \n"
	"end                                                   \n"
	"";

class ScriptComponentPrivates {
public:
	LuaFunction<bool()> start,earlyUpdate,lateUpdate,update;
	ScriptComponentPrivates(LuaTable context) :
		start(      context.Get<LuaFunction<bool()>>("start"      )),
		earlyUpdate(context.Get<LuaFunction<bool()>>("earlyUpdate")),
		update(     context.Get<LuaFunction<bool()>>("update"     )),
		lateUpdate( context.Get<LuaFunction<bool()>>("lateUpdate" ))
	{ }
};

void ScriptComponent::init() {
	lua.RunScript(script);
	LuaTable context = lua.GetGlobalEnvironment().Get<LuaTable>("context");
	this->privates = new ScriptComponentPrivates(context);

	privates->start.Invoke();
}
void ScriptComponent::earlyUpdate() {
	privates->earlyUpdate.Invoke();
}
void ScriptComponent::update() {
	privates->update.Invoke();
}

void ScriptComponent::lateUpdate() {
	privates->lateUpdate.Invoke();
}

ScriptComponent::~ScriptComponent()
{
	delete privates;
}

ScriptComponent::ScriptComponent() { }
