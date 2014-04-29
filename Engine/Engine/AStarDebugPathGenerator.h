#pragma once

#include "AStarPathGenerator.h"
#include "DebugShapeManager.h"

#include <glm/gtx/transform.hpp>

namespace AStar {
	namespace DEBUG {
		class AStarDebugPathGenerator : public AStar::PathGenerator {
			std::vector<DebugShapeManager::DebugShapeData *> NodeRenderables;
			std::vector<DebugShapeManager::DebugShapeData *> ConnectionRenderables;
			
		public:
			void printAll(DebugShapeManager& shaper, glm::vec4& nodeColor, glm::vec4& connectionColor) {
				clear();
				for (int i = 0; i < numOfGameNodes; i++)
				{
					glm::mat4 transform = glm::translate(gameNodes[i].pos);
					NodeRenderables.push_back(shaper.addUnitSphere(transform,nodeColor));
					for (int j = 0; j < gameNodes[i].numOfConnections; j++)
					{
						glm::vec3 orgin = gameNodes[i].pos;
						glm::vec3 direction = gameNodes[i].connections[j].to->pos - orgin;
						ConnectionRenderables.push_back(shaper.addUnitVector(orgin,direction,connectionColor));
					}
				}
			}
			void printNodes(DebugShapeManager& shaper, glm::vec4& nodeColor) {
				clear();
				for (int i = 0; i < numOfGameNodes; i++)
				{
					glm::mat4 transform = glm::translate(gameNodes[i].pos);
					NodeRenderables.push_back(shaper.addUnitSphere(transform,nodeColor));
				}
			}
			void clear() {
				for (int i = 0; i < NodeRenderables.size(); i++)
				{
					NodeRenderables[i]->kill();
				}
				for (int i = 0; i < ConnectionRenderables.size(); i++)
				{
					ConnectionRenderables[i]->kill();
				}
				NodeRenderables.clear();
				ConnectionRenderables.clear();
			}
		};
	}
}