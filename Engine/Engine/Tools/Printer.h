#pragma once

#include <Engine/Defines/SingletonsDefine.h>
#include <ExportHeader.h>
#include <string>

#define printer Printer::getInstance()

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
};