#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Tools/MasterLua.h>
#include <ExportHeader.h>
#include <Engine/Systems/Resources/Script.h>
#include <Engine/Systems/ResourceManager.h>

class ScriptComponentPrivates;

class ENGINE_SHARED ScriptComponent : public Component {
	LUA_OBJECT(ScriptComponent);
	static const char * LuaTemplate;
	ScriptComponentPrivates * privates;
	
public:
	Script * script;
	ScriptComponent();
	ScriptComponent(Script * script);
	ScriptComponent(int scriptId);
	~ScriptComponent();
	std::string getScriptName();
	virtual void init();
	virtual void start();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
	LuaTable getContext();
	operator LuaUserdata<ScriptComponent>();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

};