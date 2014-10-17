#include "ScriptComponent.h"
#include <luacppinterface.h>
#include <iostream>
#include <Engine/Entity/Entity.h>

const char * ScriptComponent::LuaTemplate = ""
	"you have access to context.parent                     \n"
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
	LuaTable context;
	ScriptComponentPrivates(LuaTable context) :
		context(context),
		start(      context.Get<LuaFunction<bool()>>("start"      )),
		earlyUpdate(context.Get<LuaFunction<bool()>>("earlyUpdate")),
		update(     context.Get<LuaFunction<bool()>>("update"     )),
		lateUpdate( context.Get<LuaFunction<bool()>>("lateUpdate" ))
	{
		int pony = 5;
		pony++;
	}
};

void ScriptComponent::init() {
	LUA_INSTANCE.RunScript("context = {};");
	auto context = LUA_INSTANCE.GetGlobalEnvironment().Get<LuaTable>("context");
	context.Set("parent",(LuaUserdata<Entity>)(*this->parent));
	LUA_INSTANCE.GetGlobalEnvironment().Set("context",context);
	LUA_INSTANCE.RunScript(script);
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
