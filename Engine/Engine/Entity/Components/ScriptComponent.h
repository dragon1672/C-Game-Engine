#pragma once

#include <Engine/Entity/Component.h>
#include <Engine/Tools/MasterLua.h>
#include <ExportHeader.h>

class ScriptComponentPrivates;

class ENGINE_SHARED ScriptComponent : public Component {
	static const char * LuaTemplate;
	ScriptComponentPrivates * privates;
public:
	const char * script;
	ScriptComponent();
	ScriptComponent(const char * script);
	~ScriptComponent();
	virtual void init();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
	LuaTable getContext();
	operator LuaUserdata<ScriptComponent>();
};