#pragma once

#include "ExportHeader.h"

class Character;

class ENGINE_SHARED State {
public:
	virtual void update(Character * c) = 0;
};