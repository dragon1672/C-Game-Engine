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


bool InputManager::Mouse::getMouseButtondown(int btn)
{
	GetAsyncKeyState(btn==0 ? WM_LBUTTONDOWN : WM_RBUTTONDOWN); // double tap
	return GetAsyncKeyState(btn==0 ? WM_LBUTTONDOWN: WM_RBUTTONDOWN)!=0;
}

bool InputManager::Mouse::getMouseButtonup(int btn)
{
	return !getMouseButtondown(btn);
}

wrap::vec2 InputManager::Mouse::mousePos()
{
	return currentMouse;
}

wrap::vec2 InputManager::Mouse::delta()
{
	//QCursor::
	return currentMouse-lastMouse;
}
