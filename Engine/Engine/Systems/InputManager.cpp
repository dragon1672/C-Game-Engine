#include "InputManager.h"
#include <windows.h>
#include <QtGui/QCursor>

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
