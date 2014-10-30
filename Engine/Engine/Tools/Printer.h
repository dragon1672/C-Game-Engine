#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>
#include <string>
#include <windows.h>
#include <Engine/TypeDefs.h>

#define printer Printer::getInstance()
#define printErr(level) printer.err(##level##),
#define printMsg(level) printer.msg(##level##),
#define printWarning(level) printer.warn(##level##),

class ENGINE_SHARED Printer {
	DEFINE_SINGLETON(Printer);
public:

	enum Color {
		BLACK     = 0,	DARK_BLUE = 1,	DARK_GREEN= 2,	TEAL      = 3,	DARK_RED  = 4,	DARK_PURPLE = 5,	GOLD      = 6,	GREY      = 7,
		DARK_WHITE= 8,	BLUE      = 9,	GREEN     = 10,	CYAN      = 11,	RED       = 12,	PURPLE      = 13,	YELLOW    = 14,	WHITE     = 15
	};


	void Log(const char * msg, Color color);
	void Log(std::string msg, Color color);
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

		template <typename T>
		SingleLinePrintConsole &operator , (const T &t) {
			if(disabled) return *this;
			if(spaces && insertSpace) { std::cout << ' '; }
			std::cout << t;
			insertSpace = true;
			return *this;
		}
	};
	SingleLinePrintConsole err(int level);
	SingleLinePrintConsole msg(int level);
	SingleLinePrintConsole warn(int level);


};