#include "ScriptComponent.h"
#include <luacppinterface.h>
#include <iostream>
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/Printer.h>
#include <Engine/Tools/Random/StringRandom.h>


namespace {
	void runLua(std::string toRun) {
		std::string errs = LUA_INSTANCE.RunScript(toRun);
		if(errs != Lua::NO_ERRORS) {
			printer.LogError("LUA COMPILE ERR");
			printer.LogError(errs.c_str());
		}
	}
}

const char * ScriptComponent::LuaTemplate = ""
	"function context:start() -- setup vars                       \n"
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
	void runMethod(std::string methodName) {
		LUA_INSTANCE.GetGlobalEnvironment().Set("CorbinEnginTmp",context);
		runLua("CorbinEnginTmp:"+methodName+"()");
	}
	ScriptComponentPrivates(LuaTable context) :
		context(context) { }
};

void ScriptComponent::init() {
	runLua("context = class();"
		//setting up defaults for functions
		"function context:init()        return true end \n"
		"function context:start()       return true end \n"
		"function context:earlyUpdate() return true end \n"
		"function context:update()      return true end \n"
		"function context:lateUpdate()  return true end \n"
		"");
	runLua(script->src);
	runLua("instance = context();");
	auto context = LUA_INSTANCE.GetGlobalEnvironment().Get<LuaTable>("instance");
	context.Set("parent",((LuaUserdata<Entity>)*parent));
	this->privates = new ScriptComponentPrivates(context);

	privates->runMethod("init");
}

void ScriptComponent::start() {
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
	delete privates;
}

ScriptComponent::ScriptComponent() :script(nullptr) { }

ScriptComponent::ScriptComponent(int scriptId) :script(resourceManager.getScript(scriptId))
{

}

ScriptComponent::ScriptComponent(Script * script) :script(script)
{

}

LuaTable ScriptComponent::getContext()
{
	return privates->context;
}

ScriptComponent::operator LuaUserdata<ScriptComponent>()
{
	MAKE_LUA_INSTANCE_RET(ScriptComponent,ret);
	//ret.Bind("context",&ScriptComponent::getContext);
	return ret;
}

bool ScriptComponent::isValid()
{
	return script != nullptr;
}
