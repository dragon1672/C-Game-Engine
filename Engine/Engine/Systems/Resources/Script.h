#pragma once

#include <ExportHeader.h>
#include <string>
#include <Engine\Systems\Resource.h>
#include <luacppinterface.h>


class ScriptPrivates;
class ENGINE_SHARED	Script : public Resource {
	ScriptPrivates * privates;
	std::string getUniqueName();
	std::string src;
public:
	Script();
	~Script();
	std::string Src() const;
	void Src(std::string val);
	LuaTable getClass();
	virtual void PassDownToHardWare();

	std::string getInstanceName();

	static std::string getClassTemplate(std::string class_name,std::string startFunction="--star the T", std::string updateFunction="--up the dates");

	bool isValid();
	void updateName();

	virtual std::vector<std::string> getErrors();

};