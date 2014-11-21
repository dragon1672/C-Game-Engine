#include "ScriptComponent.h"
#include <luacppinterface.h>
#include <iostream>
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/Printer.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/IO/Stream.h>

REGISTER_COMPONENT(ScriptComponent);

class ScriptComponentPrivates {
public:
	LuaTable context;
	std::string uniqueName;
	void runMethod(std::string methodName) {
		MasterLua::runLua("if(type("+uniqueName+"."+methodName+") == 'function') then "+uniqueName+":"+methodName+"(); end");
	}
	ScriptComponentPrivates(LuaTable context,std::string uniqueName) : context(context),uniqueName(uniqueName) { }
};

void ScriptComponent::start() {
	hasBeenInited = true;
	std::string instancename = myScript()->getInstanceName();
	auto context = LUA_INSTANCE.GetGlobalEnvironment().Get<LuaTable>(instancename);
	context.Set("parent",((LuaUserdata<Entity>)*parent));
	SAFE_NEW(privates,ScriptComponentPrivates(context,instancename));
	privates->runMethod("start");
}
void ScriptComponent::earlyUpdate() {
	if(!hasBeenInited) start();
	privates->runMethod("earlyUpdate");
}
void ScriptComponent::update() {
	if(!hasBeenInited) start();
	privates->runMethod("update");
}

void ScriptComponent::lateUpdate() {
	if(!hasBeenInited) start();
	privates->runMethod("lateUpdate");
}

ScriptComponent::~ScriptComponent()
{
	SAFE_DELETE(privates);
}

ScriptComponent::ScriptComponent() :script(Object::NULL_OBJECT_ID()), privates(nullptr), hasBeenInited(false) { }

ScriptComponent::ScriptComponent(int scriptId) :script(scriptId), privates(nullptr), hasBeenInited(false) { }

ScriptComponent::ScriptComponent(Script * script) :script(Object::NULL_OBJECT_ID()), privates(nullptr), hasBeenInited(false) { }

LuaTable ScriptComponent::getContext()
{
	return privates->context;
}

bool ScriptComponent::isValid()
{
	return myScript() != nullptr;
}

std::string ScriptComponent::getScriptName()
{
	return myScript() != nullptr ? myScript()->Name() : "";
}

std::vector<std::string> ScriptComponent::getErrors()
{
	std::vector<std::string> ret;
	if(myScript() == nullptr) ret.push_back("no script");
	return ret;
}

void ScriptComponent::ChildSave(Stream& s)
{
	s << script;
}

void ScriptComponent::ChildLoad(Stream& s)
{
	s >> script;
}

bool ScriptComponent::CopyInto(Component* t)
{
	if(typeid(*t) != typeid(*this)) return false;
	ScriptComponent * that = (ScriptComponent*)t;
	that->script = this->script;
	that->hasBeenInited = false;
	return true;
}

Script * ScriptComponent::myScript() const
{
	return resourceManager.getScript(script);
}

void ScriptComponent::myScript(Script * val)
{
	script = val != nullptr ? val->getID() : Object::NULL_OBJECT_ID();
}

void ScriptComponent::myScript(double val)
{
	script = val;
}

void ScriptComponent::callMethod(std::string methodName)
{
	privates->runMethod(methodName);
}
