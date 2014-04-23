#include "AStarPath.h"

namespace AStar {
	GameNode * Path::popCurrentConnection() {
		int id = nodes.size() - 1;
		currentDestination = nodes[id];
		nodes.erase(nodes.begin() + id);
		return currentDestination;
	}
	bool Path::isComplete() {
		return nodes.size() > 0;
	}
}