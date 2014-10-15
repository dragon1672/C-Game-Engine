#pragma once

#include <Engine/Entity/Component.h>
#include <luacppinterface.h>
#include <ExportHeader.h>

class ScriptComponentPrivates;

class ENGINE_SHARED ScriptComponent : public Component {
	static Lua lua;
	static const char * LuaTemplate;
	ScriptComponentPrivates * privates;
public:
	const char * script;
	ScriptComponent();
	~ScriptComponent();
	virtual void init();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
};