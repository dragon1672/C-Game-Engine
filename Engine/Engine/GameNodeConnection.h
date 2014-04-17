#pragma once

#include "ExportHeader.h"
#include <glm/glm.hpp>

struct GameNode;
struct GameNodeConnection {
	GameNode * to;
	float cost;
};