#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>
#include <string>
#include <windows.h>
#include <Engine/TypeDefs.h>
#include <iostream>
#include <Engine/Tools/Console.h>

#define printer Printer::getInstance()
#define printErr(level) printer.err(##level##),
#define printMsg(level) printer.msg(##level##),
#define printWarning(level) printer.warn(##level##),

class ENGINE_SHARED Printer {
	DEFINE_SINGLETON(Printer);
public:
	void Log(const char * msg, Console::Color color);
	void Log(std::string msg, Console::Color color);
	void LogMessage(const char * msg);
	void LogWarning(const char * msg);
	void LogError(  const char * msg);
	void LogMessage(std::string msg);
	void LogWarning(std::string msg);
	void LogError(  std::string msg);

	bool spaces;
	bool lineReturns;
	int ignoreBottomRange;
	Printer() : spaces(true), lineReturns(true), ignoreBottomRange(1) { }

	struct ENGINE_SHARED SingleLinePrintConsole {
		void* consoleHandle;
		ushort m_currentConsoleAttr;
		CONSOLE_SCREEN_BUFFER_INFO   csbi;
		bool spaces,insertSpace,lineReturn,disabled;
		SingleLinePrintConsole(int color, bool spaces, bool lineReturn, bool disabled=false);
		~SingleLinePrintConsole();
		bool printSingleVarPrep();
		void printSingleVarEnd();

		template <typename T>
		SingleLinePrintConsole &operator , (const T &t) {
			if(printSingleVarPrep()) {
				std::cout << t;
				printSingleVarEnd();
			}
			return *this;
		}
		template <typename T>
		SingleLinePrintConsole &operator << (const T &t) {
			if(printSingleVarPrep()) {
				std::cout << t;
				printSingleVarEnd();
			}
			return *this;
		}
	};
	SingleLinePrintConsole err(int level);
	SingleLinePrintConsole msg(int level);
	SingleLinePrintConsole warn(int level);


};