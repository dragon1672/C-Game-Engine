#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "ExportHeader.h"
#include "DebugShapeManager.h"

struct ENGINE_SHARED Node {
	DebugShapeManager::DebugShapeData * data;
	glm::vec3 pos;
	bool isActive;
	Node* connectedNodes[50];
	int numOfConnections;
};