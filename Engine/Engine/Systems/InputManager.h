#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>
#include <string>
#include <Engine/Tools/GlmWrap.h>
#include <Engine/Tools/MasterLua.h>
#include <glm/glm.hpp>
#include <Engine/TypeDefs.h>
#include <Engine/Tools/SingleKeyManager.h>
#include <unordered_map>
#include <Engine/Tools/Printer.h>

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
	SHIFT = 16
};
enum MouseCodes {
	LEFT_MOUSE = 2, RIGHT_MOUSE = 1, MIDDLE_MOUSE = 4
};

class QWidget;

class ENGINE_SHARED	 InputManager {
	LUA_OBJECT(InputManager);
public:
	struct ENGINE_SHARED Mouse {
	private:
		InputManager * parent;
		LUA_OBJECT(Mouse);

		wrap::vec2 mouseDelta;
		wrap::vec2 lastMouse;
		wrap::vec2 currentMouse;

		LUA_GET_FUN(wrap::vec2,mousePos);
		LUA_GET_FUN(wrap::vec2,delta);
		bool getMouseButtondown_LUA(int btn);
		bool getMouseButtonup_LUA(int btn);
	public:
		MAKE_DEFAULT_LUA_CONST_AND_DEST(Mouse);
		bool getMouseButtondown(MouseCodes btn);
		bool getMouseButtonup(MouseCodes btn);
		wrap::vec2& mousePos();
		wrap::vec2& delta();
		friend InputManager;

		operator LuaUserdata<Mouse>() {
			MAKE_LUA_INSTANCE_RET(Mouse,ret);
			ret.Bind("getMouseDown",&Mouse::getMouseButtondown_LUA);
			ret.Bind("getMouseUp"  ,&Mouse::getMouseButtonup_LUA);
			LUA_BIND_FUN(Mouse,ret,mousePos);
			LUA_BIND_FUN(Mouse,ret,delta);

			return ret;
		}
	};
private:
	LUA_GET_FUN(Mouse,getMouse);
	inline bool getKeyDown_Lua(uchar key) { return getKeyDown((KeyCode)key); }
	inline bool getKeyUp_Lua(uchar key) { return getKeyUp((KeyCode)key); }
	inline bool checkKeyClick_Lua(uchar key) { return checkKeyClick((KeyCode)key); }
	std::unordered_map<KeyCode,SingleKeyManager> trackedKeys;
	QWidget * context;
	std::function<glm::vec2()> mouseGetterFunction;
	DEFINE_SINGLETON(InputManager);
public:
	std::function<glm::vec2()> MouseGetterFunction() const { return mouseGetterFunction; }
	void MouseGetterFunction(std::function<glm::vec2()> val) { mouseGetterFunction = val; }
	QWidget * Context() const { return context; }
	void Context(QWidget * val) { context = val; }
	InputManager();
	~InputManager();
	Mouse mouse;

	bool getKeyDown(KeyCode key);
	bool getKeyUp(KeyCode key);
	bool checkKeyClick(KeyCode key);
	Mouse& getMouse() { return mouse; }

	void init();
	void update();

	operator LuaUserdata<InputManager>();
};