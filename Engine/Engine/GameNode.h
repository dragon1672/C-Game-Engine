#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include "ExportHeader.h"
#include "Ray.h"

struct GameNodeConnection;

typedef unsigned int uint;

struct ENGINE_SHARED GameNode {
	glm::vec3 pos;
	uint numOfConnections;
	GameNodeConnection * connections;
};