#pragma once
#include <utility>
#include <Engine/TypeDefs.h>

#include <ExportHeader.h>

namespace Console {
	enum Color {
		BLACK     = 0,	DARK_BLUE = 1,	DARK_GREEN= 2,	TEAL      = 3,	DARK_RED  = 4,	DARK_PURPLE = 5,	GOLD      = 6,	GREY      = 7,
		DARK_WHITE= 8,	BLUE      = 9,	GREEN     = 10,	CYAN      = 11,	RED       = 12,	PURPLE      = 13,	YELLOW    = 14,	WHITE     = 15
	};
	ENGINE_SHARED void setColor(Color foreground, Color background = Color::BLACK);
	ENGINE_SHARED void setCursorPos(short x, short y);
	ENGINE_SHARED void setCursorPos(std::pair<long,long> pos);
	ENGINE_SHARED std::pair<long,long> getCursorPos();
	ENGINE_SHARED void setCursorVisability(bool shown);
	ENGINE_SHARED void hideCursor();
	ENGINE_SHARED void showCursor();
	ENGINE_SHARED void ClearConsole(const int foreground = Color::GREEN, const int background = Color::BLACK);
	ENGINE_SHARED void maximize();
	ENGINE_SHARED void setWindowVisability(bool shown);
	ENGINE_SHARED void hideWindow();
	ENGINE_SHARED void showWindow();


	void PrintLoadingBar(std::pair<long,long> pos, int iteration, int maxIteration, uint length);
}