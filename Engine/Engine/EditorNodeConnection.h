#pragma once

#include "ExportHeader.h"
#include <glm/glm.hpp>
#include "DebugShapeManager.h"
#include "EditorNode.h"

struct EditorNodeConnection {
	EditorNode * to;
	float cost;
	DebugShapeManager::DebugShapeData * renderable;
};