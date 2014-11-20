#include "Console.h"
#include <windows.h>
#include <Engine/Tools/StringManapulation.h>
#include <iostream>



namespace Console {
	void setColor(Color foreground, Color background /*= Color::BLACK*/)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, ((WORD)foreground+((WORD)background*16)) );
		return;
	}

	void setCursorPos(short x, short y)
	{
		COORD position = {x, y};
		SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), position );
	}

	void setCursorPos(std::pair<long,long> pos)
	{
		setCursorPos((short)pos.first,(short)pos.second);
	}

	std::pair<long,long> getCursorPos()
	{
		LPPOINT cur = nullptr;
		if(!GetCursorPos(cur)) {
			//err
		}
		return std::pair<long,long>(cur->x,cur->y);
	}

	void setCursorVisability(bool shown)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursoInfo;
		CursoInfo.dwSize = shown ? 10 : 1;
		CursoInfo.bVisible = shown;
		SetConsoleCursorInfo(hConsole, &CursoInfo);
		return;
	}

	void hideCursor()
	{
		setCursorVisability(false);
	}

	void showCursor()
	{
		setCursorVisability(true);
	}

	void ClearConsole(const int foreground /*= Color::GREEN*/, const int background /*= Color::BLACK*/)
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

	void maximize()
	{
		HWND hwnd = FindWindow(L"ConsoleWindowClass", NULL);
		ShowWindow(hwnd,SW_SHOWMAXIMIZED);
	}

	void setWindowVisability(bool shown)
	{
		HWND hwnd = FindWindow(L"ConsoleWindowClass", NULL);
		ShowWindow(hwnd,shown?SW_SHOWNORMAL:SW_HIDE);
	}

	void hideWindow()
	{
		setWindowVisability(false);
	}

	void showWindow()
	{
		setWindowVisability(true);
	}


	bool updateProgressBar(int iteration, int maxIterator, int barLength)
	{
		return (iteration % (maxIterator / barLength) == 0) // mid bar
			|| (barLength > maxIterator)
			|| iteration == maxIterator - 1 // bar is complete
			|| iteration == 0;
	}

	void PrintLoadingBar(std::pair<long,long> pos, int iteration, int maxIteration, uint length)
	{
		if(!updateProgressBar(iteration,maxIteration,length)) return;
		float percent = (float)iteration/(float)maxIteration;
		setCursorPos(pos);
		std::cout << StringManapulation::LoadingBar(percent,length,true);
	}

}
