#include "Script.h"
#include <Engine/Tools/MasterLua.h>
#include <Engine/Tools/StringManapulation.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <Engine/TypeDefs.h>
#include <Engine/Defines/SafeNewAndDelete.h>
#include <Engine/IO/Stream.h>


namespace {
	std::string extractName(std::string src) {
		std::string startString = "--class ";
		if(StringManapulation::startsWith(src,startString)) {
			std::string name;
			for (uint i = startString.length(); i < src.length(); i++)
			{
				if(src[i]=='\n') break;
				else name += src[i];
			}
			return StringManapulation::trimWhiteSpace(name);
		}
		return "";
	}
}

class ScriptPrivates {
public:
	LuaTable context;
	ScriptPrivates(LuaTable context) : context(context) {}
};


void Script::PassDownToHardWare()
{
	//get ma name
	Name(extractName(src));
	if(Name() == "") throw std::bad_function_call("Invalid Script, unable to discover name");

	//set up base
	MasterLua::runLua(Name()+" = class("+MasterLua::ComponentBaseClass+");");

	//run user stuff to override functions
	MasterLua::runLua(src);

	//snag dat
	auto context = LUA_INSTANCE.GetGlobalEnvironment().Get<LuaTable>(Name());

	//save dat
	SAFE_NEW(privates,ScriptPrivates(context));
}


Script::Script() : privates(nullptr)
{

}

LuaTable Script::getClass()
{
	return privates->context;
}

Script::~Script()
{
	SAFE_DELETE(privates);
}

bool Script::isValid()
{
	return StringManapulation::startsWith(src,"--class ");
}

std::string Script::getClassTemplate(std::string class_name,std::string startFunction/*="--star the T"*/, std::string updateFunction/*="--up the dates"*/)
{
	return ""
		"--class "+class_name+"                       \n"
		"--above line is required as the first line   \n"
		"                                             \n"
		"--available functions                        \n"
		"--start,earlyUpdate,update,lateUpdate        \n"
		"                                             \n"
		"                                             \n"
		"function "+class_name+":start()              \n"
		"   "+startFunction+"                         \n"
		"end                                          \n"
		"                                             \n"
		"function "+class_name+":update()             \n"
		"   "+updateFunction+"                        \n"
		"end                                          \n"
		"                                             \n"
		"";
}

std::string Script::getUniqueName()
{
	return Random::rString::Letters(5)+"CorbinEngin"+Name()+"InstanceID"+Random::rString::Letters(5);
}

std::string Script::getInstanceName()
{
	//create copy
	std::string instanceName = getUniqueName();
	MasterLua::runLua(instanceName+" = "+Name()+"();");
	return instanceName;
}

std::vector<std::string> Script::getErrors()
{
	std::vector<std::string> ret;
	if(!StringManapulation::startsWith(src,"--class ")) ret.push_back("Invalid Script, unable to discover name");
	return ret;
}

void Script::updateName()
{
	Name(extractName(src));
}

void Script::Src(std::string val)
{
	src = val;
	updateName();
}

std::string Script::Src() const
{
	return src;
}

void Script::ChildSave(Stream& s)
{
	s << src;
}

void Script::ChildLoad(Stream& s)
{
	s >> src;
}
