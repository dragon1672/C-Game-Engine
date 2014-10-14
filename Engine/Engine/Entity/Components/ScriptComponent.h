#pragma once

#include <Engine/Entity/Component.h>
#include <luacppinterface.h>
#include <ExportHeader.h>

class ENGINE_SHARED ScriptComponent : public Component {
	static Lua lua;
	LuaTable context;
public:
	const char * script;
	ScriptComponent();
	virtual void init();
	virtual void earlyUpdate();
	virtual void update();
	virtual void lateUpdate();
};