#pragma once

#include <ExportHeader.h>
#include <string>
#include <Engine\Systems\Resource.h>
#include <luacppinterface.h>


class ScriptPrivates;
class ENGINE_SHARED	MAKE_RESOURCE_CLASS(Script) {
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

	static std::string getScriptComponentTemplate(std::string class_name,std::string startFunction="--star the T", std::string updateFunction="--up the dates");
	static std::string getScriptFileTemplate(std::string class_name,std::string fileStuffs="--put classname = class(stuff)") {
		return "--class "+class_name+"                       \n"
			"--above line is required as the first line   \n"
			"                                             \n"
			+fileStuffs+
			"";
	}
	
	bool isValid();
	void updateName();

	virtual std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

	bool equals(Script& that) const;

};