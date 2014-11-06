#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Tools/MasterLua.h>
#include <ExportHeader.h>
#include <Engine/Systems/Resources/Script.h>
#include <Engine/Systems/ResourceManager.h>

class ScriptComponentPrivates;

class ENGINE_SHARED ScriptComponent : public Component {
	ScriptComponentPrivates * privates;
	Script * script;
public:
	Script * myScript() const { return script; }
	void myScript(Script * val) { script = val; }
	ScriptComponent();
	ScriptComponent(Script * script);
	ScriptComponent(int scriptId);
	~ScriptComponent();
	std::string getScriptName();
	virtual void start();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
	LuaTable getContext();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

};