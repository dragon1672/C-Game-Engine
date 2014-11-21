#include "Console.h"
#include <windows.h>
#include <Engine/Tools/StringManapulation.h>
#include <iostream>
#include <Engine/Tools/Printer.h>



namespace Console {
	void setColor(Color foreground, Color background /*= Color::BLACK*/)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, ((WORD)foreground+((WORD)background*16)) );
		return;
	}

	void setCursorPos(short x, short y)
	{
		COORD position = {x,y};
		if(!SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), position )) {
			printErr(100) "set cursor failed with",GetLastError();
		}
	}

	void setCursorPos(std::pair<int,int> pos)
	{
		setCursorPos((short)pos.first,(short)pos.second);
	}

	ENGINE_SHARED std::pair<int,int> getCursorPos()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi )) {
			printErr(100) "get cursor failed with",GetLastError();
			return std::pair<int,int>(-1,-1);
		}
		
		return std::pair<int,int>(csbi.dwCursorPosition.X,csbi.dwCursorPosition.Y);
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
		return (barLength > maxIterator) // each iteration will require update
			|| (iteration % (maxIterator / barLength) == 0) // mid bar
			|| iteration == maxIterator // bar is complete
			|| iteration == 0;
	}

	bool PrintLoadingBar(std::pair<long,long> pos, int iteration, int maxIteration, uint length)
	{
		if(!updateProgressBar(iteration,maxIteration,length)) return false;
		float percent = (float)iteration/(float)maxIteration;
		setCursorPos(pos);
		std::cout << StringManapulation::LoadingBar(percent,length,true) << std::endl;
		return true;
	}

	int CursorXPos()
	{
		return getCursorPos().first;
	}

	int CursorYPos()
	{
		return getCursorPos().second;
	}

}
