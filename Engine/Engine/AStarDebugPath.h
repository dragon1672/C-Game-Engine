#pragma once

#include "AStarPath.h"
#include "DebugShapeManager.h"

namespace AStar {
	namespace DEBUG {
		struct ENGINE_SHARED DebugPath : public Path {
			std::vector<DebugShapeManager::DebugShapeData*> NodeRenderables;
			std::vector<DebugShapeManager::DebugShapeData*> ConnectionRenderables;
			void drawPath(DebugShapeManager& shapeManager, glm::vec3& currentPos);
			
			glm::vec3 popCurrentConnection(); // override
		};
	}
}