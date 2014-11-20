#include "Console.h"
#include <windows.h>


void Console::setColor(Color foreground, Color background /*= Color::BLACK*/)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ((WORD)foreground+((WORD)background*16)) );
	return;
}

void Console::setCursorPos(short x, short y)
{
	COORD position = {x, y};
	SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), position );
}

std::pair<long,long> Console::getCursorPos()
{
	LPPOINT cur = nullptr;
	if(!GetCursorPos(cur)) {
		//err
	}
	return std::pair<long,long>(cur->x,cur->y);
}

void Console::setCursorVisability(bool shown)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursoInfo;
	CursoInfo.dwSize = shown ? 10 : 1;
	CursoInfo.bVisible = shown;
	SetConsoleCursorInfo(hConsole, &CursoInfo);
	return;
}

void Console::hideCursor()
{
	setCursorVisability(false);
}

void Console::showCursor()
{
	setCursorVisability(true);
}

void Console::ClearConsole(const int foreground /*= Color::GREEN*/, const int background /*= Color::BLACK*/)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {return;}
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	SetConsoleTextAttribute(hConsole, (WORD)(foreground+(background*16)) );
	SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coordScreen );//resetting position
	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)) {return;}
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {return;}
	if (!FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {return;}
	return;
}

void Console::maximize()
{
	HWND hwnd = FindWindow(L"ConsoleWindowClass", NULL);
	ShowWindow(hwnd,SW_SHOWMAXIMIZED);
}

void Console::setWindowVisability(bool shown)
{
	HWND hwnd = FindWindow(L"ConsoleWindowClass", NULL);
	ShowWindow(hwnd,shown?SW_SHOWNORMAL:SW_HIDE);
}

void Console::hideWindow()
{
	setWindowVisability(false);
}

void Console::showWindow()
{
	setWindowVisability(true);
}
