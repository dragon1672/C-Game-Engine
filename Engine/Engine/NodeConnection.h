#pragma once

#include "ExportHeader.h"
#include <glm/glm.hpp>
#include "Node.h"
#include "DebugShapeManager.h"

struct NodeConnection {
	Node * from;
	Node * to;
	DebugShapeManager::DebugShapeData * renderable;
};