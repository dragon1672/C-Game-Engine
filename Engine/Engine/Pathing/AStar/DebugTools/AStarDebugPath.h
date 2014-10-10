#pragma once

#include <Engine/Pathing/AStar/AStarPath.h>
#include <Engine/DebugTools/DebugShapeManager.h>

#define ENABLE_DEBUG_SHAPES

namespace AStar {
	namespace DEBUG {
		struct ENGINE_SHARED DebugPath : public Path {
#ifdef ENABLE_DEBUG_SHAPES
			std::vector<DebugShapeManager::DebugShapeData*> NodeRenderables;
			std::vector<DebugShapeManager::DebugShapeData*> ConnectionRenderables;
			DebugShapeManager::DebugShapeData * currentNodeRenderable;
			
			DebugPath() {
				currentNodeRenderable = nullptr;
			}
			inline void load(AStar::Path& src) {
				this->currentDestination = src.currentDestination;
				this->positions          = src.positions;
				this->validPath          = src.validPath;
			}

			void drawPath(DebugShapeManager& shapeManager);

			glm::vec3 popCurrentConnection(); // override
			void setVisability(bool newState);
			void resetGraphics(DebugShapeManager& shapeManager);
#else
			void drawPath(DebugShapeManager& shapeManager, glm::vec3& currentPos) {}
			void setVisability(bool newState) {}
			void resetGraphics() {}
#endif
		};
	}
}