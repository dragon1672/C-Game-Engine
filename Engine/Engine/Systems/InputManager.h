#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>
#include <string>
#include <Engine/Tools/GlmWrap.h>
#include <Engine/Tools/MasterLua.h>
#include <glm/glm.hpp>
#include <Engine/TypeDefs.h>

#define inputManager InputManager::getInstance()

enum KeyCode {
	A = 65,		B = 66,		C = 67,		D = 68,	
	E = 69,		F = 70,		G = 71,		H = 72,	
	I = 73,		J = 74,		K = 75,		L = 76,	
	M = 77,		N = 78,		O = 79,		P = 80,	
	Q = 81,		R = 82,		S = 83,		T = 84,	
	U = 85,		V = 86,		W = 87,		X = 88,	
	Y = 89,		Z = 90,		ZERO = 48,	One = 49,
	TWO = 50,	THREE = 51, FOUR = 52,	FIVE = 53,
	SIX = 54,	SEVEN = 55,	EIGHT = 56,	NINE = 57,
};

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

	bool getKeyDown(KeyCode key);
	bool getKeyUp(KeyCode key);
	Mouse getMouse() { return mouse; }

	LUA_GET_FUN(Mouse,getMouse);
	inline bool getKeyDown_Lua(uchar key) { return getKeyDown((KeyCode)key); }
	inline bool getKeyUp_Lua(uchar key) { return getKeyUp((KeyCode)key); }

	void init();
	void update();

	operator LuaUserdata<InputManager>() {
		MAKE_LUA_INSTANCE_RET(InputManager,ret);
		ret.Bind("getKeyDown",&InputManager::getKeyDown_Lua);
		ret.Bind("getKeyUp",  &InputManager::getKeyUp_Lua);
		LUA_BIND_FUN(InputManager,ret,getMouse);

		return ret;
	}
};