#include "Printer.h"
#include <windows.h>
#include <iostream>
#include <Engine/TypeDefs.h>
#include <Engine/DebugTools/DebugMemHeader.h>

namespace {
	void removeCursor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursoInfo;
		CursoInfo.dwSize = 1;
		CursoInfo.bVisible = false;
		SetConsoleCursorInfo(hConsole, &CursoInfo);
		return;
	}
	void addCursor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursoInfo;
		CursoInfo.dwSize = 10;
		CursoInfo.bVisible = true;
		SetConsoleCursorInfo(hConsole, &CursoInfo);
		return;
	}
	void go2xy(short x, short y) {//requires <windows.h>
		COORD position = {x, y};
		SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), position );
	}
	void SetColor(const int foreground) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (ushort)foreground);
		return;
	}
	void SetColor(const int foreground, const int background) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (ushort)(foreground+(background*16)) );
		return;
	}
	void ClearConsole(const int foreground, const int background) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {return;}
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		SetConsoleTextAttribute(hConsole, (ushort)(foreground+(background*16)) );
		SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coordScreen );//resetting position
		if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)) {return;}
		if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {return;}
		if (!FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {return;}
		return;
	}
}

IMPLEMENT_SINGLETON(Printer);

void Printer::LogMessage(const char * msg) { Log(msg,Color::GREEN);  }

void Printer::LogMessage(std::string msg)
{
	LogMessage( msg.c_str() );
}

void Printer::LogWarning(const char * msg) { Log(msg,Color::YELLOW); }

void Printer::LogWarning(std::string msg)
{
	LogWarning( msg.c_str() );
}

void Printer::LogError(const char * msg)   { Log(msg,Color::RED);    }

void Printer::LogError(std::string msg)
{
	LogError(   msg.c_str() );
}

void Printer::Log(const char * msg, Color color)
{
	SetColor(color);
	std::cout << msg << std::endl;
	SetColor(Color::GREEN);
}

void Printer::Log(std::string msg, Color color)
{
	Log(msg.c_str(),color);
}

Printer::SingleLinePrintConsole Printer::warn(int level)
{
	return SingleLinePrintConsole(Printer::Color::YELLOW,spaces,lineReturns,level < ignoreBottomRange);
}

Printer::SingleLinePrintConsole Printer::msg(int level)
{
	return SingleLinePrintConsole(-1,spaces,lineReturns,level < ignoreBottomRange);
}

Printer::SingleLinePrintConsole Printer::err(int level)
{
	return SingleLinePrintConsole(Printer::Color::RED,spaces,lineReturns,level < ignoreBottomRange);
}

Printer::SingleLinePrintConsole::SingleLinePrintConsole(int color, bool spaces, bool lineReturn,bool disabled /* = false */)
	:
	spaces(spaces), lineReturn(lineReturn),insertSpace(false),disabled(disabled)
{
	if(disabled) return;
	insertSpace = false;
	consoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);
	if(GetConsoleScreenBufferInfo(consoleHandle, &csbi)) {
		m_currentConsoleAttr = csbi.wAttributes;
	}
	SetConsoleTextAttribute ( consoleHandle, (ushort)color);
}

Printer::SingleLinePrintConsole::~SingleLinePrintConsole()
{
	if(disabled) return;
	if(lineReturn) { std::cout << std::endl; }
	SetConsoleTextAttribute ( consoleHandle, m_currentConsoleAttr);
}
