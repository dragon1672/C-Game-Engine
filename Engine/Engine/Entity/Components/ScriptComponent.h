#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Tools/MasterLua.h>
#include <ExportHeader.h>
#include <Engine/Systems/Resources/Script.h>
#include <Engine/Systems/ResourceManager.h>

class ScriptComponentPrivates;

class ENGINE_SHARED ScriptComponent : public Component {
	static const char * LuaTemplate;
	ScriptComponentPrivates * privates;
	
public:
	Script * script;
	ScriptComponent();
	ScriptComponent(Script * script) :script(script) { }
	ScriptComponent(int scriptId) :script(resourceManager.getFirstScript(scriptId)) { }
	~ScriptComponent();
	virtual void init();
	virtual void start();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
	LuaTable getContext();
	operator LuaUserdata<ScriptComponent>();
};