#include "Script.h"
#include <Engine/Tools/Random/StringRandom.h>
#include <Engine/Tools/MasterLua.h>



Script::Script() : context(nullptr)
{

}

LuaTable& Script::getContext()
{
	return *context;
}

void Script::callFunction(std::string methodName)
{
	std::string name = "CORBIN_ENGINE_TMP_";
	name += Random::rString::Letters(5);

	LUA_INSTANCE.GetGlobalEnvironment().Set(name,*context);
	getContext().Set(name,*context);
	LUA_INSTANCE.RunScript(name+":"+methodName+"()");
}
