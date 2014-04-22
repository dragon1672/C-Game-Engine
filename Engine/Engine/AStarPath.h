#pragma once

#include "AStarNode.h"
#include <vector>

namespace AStar {
	struct Path {
		std::vector<GameNode *> nodes;
		GameNode * currentDestination;

		GameNode * popCurrentConnection() {
			currentDestination = nodes[0];
			nodes.erase(nodes.begin() + 0);
			return currentDestination;
		}
		bool isComplete() {
			return nodes.size() > 0;
		}
	};
}