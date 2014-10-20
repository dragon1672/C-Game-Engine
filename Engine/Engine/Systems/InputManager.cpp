#include "InputManager.h"
#include <windows.h>
#include <QtGui/QCursor>

IMPLEMENT_SINGLETON(InputManager);

void InputManager::init()
{
	mouse.lastMouse = mouse.currentMouse = wrap::vec2(QCursor::pos().x,QCursor::pos().y);
}

void InputManager::update()
{
	mouse.lastMouse = mouse.currentMouse;
	mouse.currentMouse = wrap::vec2(QCursor::pos().x,QCursor::pos().y);
}

bool InputManager::getKeyDown(int key)
{
	GetAsyncKeyState(key); // double tap
	return GetAsyncKeyState(key)==0;
}
bool InputManager::getKeyDown(int key)
{
	return !getKeyUp(key);
}


bool InputManager::Mouse::getMouseButtondown(int btn)
{
	GetAsyncKeyState(btn==0 ? WM_LBUTTONDOWN : WM_RBUTTONDOWN); // double tap
	return GetAsyncKeyState(btn==0 ? WM_LBUTTONDOWN: WM_RBUTTONDOWN)==0;
}

bool InputManager::Mouse::getMouseButtonup(int btn)
{
	GetAsyncKeyState(btn==0 ? WM_LBUTTONUP : WM_RBUTTONUP); // double tap
	return GetAsyncKeyState(btn==0 ? WM_LBUTTONUP : WM_RBUTTONUP)==0;
}

wrap::vec2 InputManager::Mouse::mousePos()
{
	return currentMouse;
}

wrap::vec2 InputManager::Mouse::delta()
{
	QCursor::
}
