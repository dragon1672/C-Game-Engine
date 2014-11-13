#include "ScriptComponent.h"
#include <luacppinterface.h>
#include <iostream>
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/Printer.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/IO/Stream.h>


class ScriptComponentPrivates {
public:
	LuaTable context;
	std::string uniqueName;
	void runMethod(std::string methodName) {
		MasterLua::runLua(uniqueName+":"+methodName+"()");
	}
	ScriptComponentPrivates(LuaTable context,std::string uniqueName) : context(context),uniqueName(uniqueName) { }
};

void ScriptComponent::start() {
	std::string instancename = script->getInstanceName();
	auto context = LUA_INSTANCE.GetGlobalEnvironment().Get<LuaTable>(instancename);
	context.Set("parent",((LuaUserdata<Entity>)*parent));
	SAFE_NEW(privates,ScriptComponentPrivates(context,instancename));
	privates->runMethod("start");
}
void ScriptComponent::earlyUpdate() {
	privates->runMethod("earlyUpdate");
}
void ScriptComponent::update() {
	privates->runMethod("update");
}

void ScriptComponent::lateUpdate() {
	privates->runMethod("lateUpdate");
}

ScriptComponent::~ScriptComponent()
{
	SAFE_DELETE(privates);
}

ScriptComponent::ScriptComponent() :script(nullptr), privates(nullptr) { }

ScriptComponent::ScriptComponent(int scriptId) :script(resourceManager.getScript(scriptId)), privates(nullptr) { }

ScriptComponent::ScriptComponent(Script * script) :script(script), privates(nullptr) { }

LuaTable ScriptComponent::getContext()
{
	return privates->context;
}

bool ScriptComponent::isValid()
{
	return script != nullptr;
}

std::string ScriptComponent::getScriptName()
{
	return script != nullptr ? script->Name() : "";
}

std::vector<std::string> ScriptComponent::getErrors()
{
	std::vector<std::string> ret;
	if(script == nullptr) ret.push_back("no script");
	return ret;
}

void ScriptComponent::ChildSave(Stream& s)
{
	s << script->getID();
}

void ScriptComponent::ChildLoad(Stream& s)
{
	double id;
	s >> id;
	script = resourceManager.getScript(id);
}

bool ScriptComponent::CopyInto(Component* t)
{
	if(typeid(*t) != typeid(*this)) return false;
	ScriptComponent * that = (ScriptComponent*)t;
	that->script = this->script;
	that->start();
	return true;
}
