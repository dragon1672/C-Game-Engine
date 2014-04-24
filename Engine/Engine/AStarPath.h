#pragma once

#include "AStarNode.h"
#include <vector>
#include "ExportHeader.h"

namespace AStar {
	struct ENGINE_SHARED Path {
		std::vector<glm::vec3> positions;
		glm::vec3 currentDestination;

		bool validPath; // false if invalid path

		glm::vec3 popCurrentConnection();
		bool isComplete();
	};
}