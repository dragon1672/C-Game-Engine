#include "ScriptComponent.h"
#include <luacppinterface.h>
#include <iostream>
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/Printer.h>

const char * ScriptComponent::LuaTemplate = ""
	"function context:init() -- setup vars                        \n"
	"    self.exampleVar = 5;                                     \n"
	"    return true                                              \n"
	"end                                                          \n"
	"function context:earlyUpdate()                               \n"
	"    return true                                              \n"
	"end                                                          \n"
	"function context:update() -- primary place to update vars    \n"
	"    self.a = self.a + 1                                      \n"
	"    print(self.a)                                            \n"
	"    return true                                              \n"
	"end                                                          \n"
	"function context:lateUpdate()                                \n"
	"                                                             \n"
	"    return true                                              \n"
	"end                                                          \n"
	"";

class ScriptComponentPrivates {
public:
	LuaTable context;
	ScriptComponentPrivates(LuaTable context) :
		context(context) { }
};

void ScriptComponent::init() {
	LUA_INSTANCE.RunScript("context = class();");
	std::string errs = LUA_INSTANCE.RunScript(script);
	if(errs != Lua::NO_ERRORS) {
		printer.LogErr("LUA COMPILE ERR");
	}
	LUA_INSTANCE.RunScript("instance = context();");
	auto context = LUA_INSTANCE.GetGlobalEnvironment().Get<LuaTable>("instance");
	context.Set("parent",((LuaUserdata<Entity>)*parent));
	this->privates = new ScriptComponentPrivates(context);

	LUA_INSTANCE.GetGlobalEnvironment().Set("CorbinEnginTmp",privates->context);
	LUA_INSTANCE.RunScript("CorbinEnginTmp:start()");
}
void ScriptComponent::earlyUpdate() {
	LUA_INSTANCE.GetGlobalEnvironment().Set("CorbinEnginTmp",privates->context);
	LUA_INSTANCE.RunScript("CorbinEnginTmp:earlyUpdate()");
}
void ScriptComponent::update() {
	LUA_INSTANCE.GetGlobalEnvironment().Set("CorbinEnginTmp",privates->context);
	LUA_INSTANCE.RunScript("CorbinEnginTmp:update()");
}

void ScriptComponent::lateUpdate() {
	LUA_INSTANCE.GetGlobalEnvironment().Set("CorbinEnginTmp",privates->context);
	LUA_INSTANCE.RunScript("CorbinEnginTmp:lateUpdate()");
}

ScriptComponent::~ScriptComponent()
{
	delete privates;
}

ScriptComponent::ScriptComponent() { }

ScriptComponent::ScriptComponent(const char * script)
{
	this->script = script;
}

LuaTable ScriptComponent::getContext()
{
	return privates->context;
}

ScriptComponent::operator LuaUserdata<ScriptComponent>()
{
	MAKE_LUA_INSTANCE_RET(ScriptComponent,ret);
	ret.Bind("context",&ScriptComponent::getContext);
	return ret;
}
