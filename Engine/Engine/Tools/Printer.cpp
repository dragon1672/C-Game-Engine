#include "Printer.h"
#include <windows.h>
#include <iostream>
#include <Engine/TypeDefs.h>
#include <Engine/DebugTools/DebugMemHeader.h>

IMPLEMENT_SINGLETON(Printer);

void Printer::LogMessage(const char * msg) { Log(msg,Console::Color::GREEN);  }

void Printer::LogMessage(std::string msg)
{
	LogMessage( msg.c_str() );
}

void Printer::LogWarning(const char * msg) { Log(msg,Console::Color::YELLOW); }

void Printer::LogWarning(std::string msg)
{
	LogWarning( msg.c_str() );
}

void Printer::LogError(const char * msg)   { Log(msg,Console::Color::RED);    }

void Printer::LogError(std::string msg)
{
	LogError(   msg.c_str() );
}

void Printer::Log(const char * msg, Console::Color color)
{
	Console::setColor(color);
	std::cout << msg << std::endl;
	Console::setColor(Console::Color::GREEN);
}

void Printer::Log(std::string msg, Console::Color color)
{
	Log(msg.c_str(),color);
}

Printer::SingleLinePrintConsole Printer::warn(int level)
{
	return SingleLinePrintConsole(Console::Color::YELLOW,spaces,lineReturns,level < ignoreBottomRange);
}

Printer::SingleLinePrintConsole Printer::msg(int level)
{
	return SingleLinePrintConsole(-1,spaces,lineReturns,level < ignoreBottomRange);
}

Printer::SingleLinePrintConsole Printer::err(int level)
{
	return SingleLinePrintConsole(Console::Color::RED,spaces,lineReturns,level < ignoreBottomRange);
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

bool Printer::SingleLinePrintConsole::printSingleVarPrep()
{
	if(disabled) return false;
	if(spaces && insertSpace) { std::cout << ' '; }
	return true;
}

void Printer::SingleLinePrintConsole::printSingleVarEnd()
{
	insertSpace = true;
}
