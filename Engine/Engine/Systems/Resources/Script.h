#pragma once

#include <ExportHeader.h>
#include <string>
#include <Engine\Systems\Resource.h>
#include <luacppinterface.h>


class ScriptPrivates;
class ENGINE_SHARED	Script : public Resource {
	ScriptPrivates * privates;
	std::string getUniqueName();
public:
	Script();
	Script(std::string name);
	~Script();
	std::string src;
	LuaTable getClass();
	virtual void PassDownToHardWare();

	std::string getInstanceName();

	static std::string getClassTemplate(std::string class_name,std::string startFunction="--star the T", std::string updateFunction="--up the dates");

	bool isValid();
	void updateName();

	virtual std::vector<std::string> getErrors();

};