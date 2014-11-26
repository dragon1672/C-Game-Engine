#include "InputManager.h"
#include <windows.h>
#include <QtGui/QCursor>
#include <Engine/DebugTools/DebugMemHeader.h>
#include <Engine/Tools/CollectionEditing.h>
#include <Engine/Tools/Timer.h>
#include <Engine/Tools/Printer.h>

IMPLEMENT_SINGLETON(InputManager);

void InputManager::init()
{
	mouse.lastMouse = mouse.currentMouse = wrap::vec2(QCursor::pos().x(),QCursor::pos().y());
}

void InputManager::update()
{
	mouse.lastMouse = mouse.currentMouse;
	mouse.currentMouse = wrap::vec2(QCursor::pos().x(),QCursor::pos().y());
	mouse.mouseDelta = mouse.currentMouse - mouse.lastMouse;
	for(auto& k : trackedKeys) {
		k.second.update(Timer::getInstance().deltaTime());
	}
}

bool InputManager::getKeyDown(KeyCode key)
{
	bool ret = GetAsyncKeyState(key)!=0 || GetAsyncKeyState(key)!=0;
	if(key == 'A' && ret || key != 'A') {
		int breaker = 0;
		breaker++;
	}
	return ret;
}
bool InputManager::getKeyUp(KeyCode key)
{
	return !getKeyDown(key);
}

InputManager::operator LuaUserdata<InputManager>()
{
	MAKE_LUA_INSTANCE_RET(InputManager,ret);
	ret.Bind("getKeyDown",&InputManager::getKeyDown_Lua);
	ret.Bind("getKeyUp",  &InputManager::getKeyUp_Lua);
	ret.Bind("getKeyClicked", &InputManager::checkKeyClick_Lua);
	LUA_BIND_FUN(InputManager,ret,getMouse);

	return ret;
}

bool InputManager::checkKeyClick(KeyCode key)
{
	if(!Collections::contains(trackedKeys,key)) {
		trackedKeys.emplace(key,SingleKeyManager(key));
		trackedKeys[key].update(Timer::getInstance().deltaTime());
	}
	return trackedKeys[key].hasBeenClicked();
}

bool InputManager::Mouse::getMouseButtondown(MouseCodes btn)
{
	return GetAsyncKeyState(btn)!=0;
}

bool InputManager::Mouse::getMouseButtonup(MouseCodes btn)
{
	return !getMouseButtondown(btn);
}

wrap::vec2&InputManager::Mouse::mousePos()
{
	return currentMouse;
}

wrap::vec2& InputManager::Mouse::delta()
{
	return mouseDelta;
}

bool InputManager::Mouse::getMouseButtondown_LUA(int btn)
{
	return getMouseButtondown((MouseCodes)btn);
}

bool InputManager::Mouse::getMouseButtonup_LUA(int btn)
{
	return getMouseButtonup((MouseCodes)btn);
}
