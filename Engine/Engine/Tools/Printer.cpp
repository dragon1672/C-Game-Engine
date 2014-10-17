#include "Printer.h"
#include <windows.h>
#include <iostream>
#include <Engine/TypeDefs.h>

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
void Printer::LogWarning(const char * msg) { Log(msg,Color::YELLOW); }
void Printer::LogError(const char * msg)   { Log(msg,Color::RED);    }

void Printer::Log(const char * msg, Color color)
{
	SetColor(color);
	std::cout << msg << std::endl;
}
