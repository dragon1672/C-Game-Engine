#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>
#include <string>
#include <Engine/Tools/GlmWrap.h>
#include <Engine/Tools/MasterLua.h>
#include <glm/glm.hpp>

#define inputManager InputManager::getInstance()

class ENGINE_SHARED	 InputManager {
	DEFINE_SINGLETON(InputManager);
public:
	struct ENGINE_SHARED Mouse {
	private:
		wrap::vec2 lastMouse;
		wrap::vec2 currentMouse;
	public:
		bool getMouseButtondown(int btn);
		bool getMouseButtonup(int btn);
		wrap::vec2 mousePos();
		wrap::vec2 delta();
		friend InputManager;

		LUA_GET_FUN(wrap::vec2,mousePos);
		LUA_GET_FUN(wrap::vec2,delta);

		operator LuaUserdata<Mouse>() {
			MAKE_LUA_INSTANCE_RET(Mouse,ret);
			ret.Bind("getMouseDown",&Mouse::getMouseButtondown);
			ret.Bind("getMouseDown",&Mouse::getMouseButtondown);
			LUA_BIND_FUN(Mouse,ret,mousePos);
			LUA_BIND_FUN(Mouse,ret,delta);

			return ret;
		}
	};
	Mouse mouse;

	bool getKeyDown(int key);
	bool getKeyUp(int key);
	Mouse getMouse() { return mouse; }

	LUA_GET_FUN(Mouse,getMouse);

	void init();
	void update();

	operator LuaUserdata<InputManager>() {
		MAKE_LUA_INSTANCE_RET(InputManager,ret);
		ret.Bind("getKeyDown",&InputManager::getKeyDown);
		ret.Bind("getKeyUp",  &InputManager::getKeyUp);
		LUA_BIND_FUN(InputManager,ret,getMouse);

		return ret;
	}
};