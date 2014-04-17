#pragma once

#include "ExportHeader.h"
#include <glm/glm.hpp>
#include "GameNode.h"

struct GameNodeConnection {
	GameNode * to;
	float cost;
};