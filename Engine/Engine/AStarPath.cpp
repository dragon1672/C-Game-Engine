#include "AStarPath.h"

namespace AStar {
	glm::vec3 Path::popCurrentConnection() {
		int id = positions.size() - 1;
		currentDestination = positions[id];
		positions.erase(positions.begin() + id);
		return currentDestination;
	}
	bool Path::isComplete() {
		return positions.size() > 0;
	}
}