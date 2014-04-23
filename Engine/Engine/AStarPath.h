#pragma once

#include "AStarNode.h"
#include <vector>
#include "ExportHeader.h"

namespace AStar {
	struct ENGINE_SHARED Path {
		std::vector<GameNode *> nodes;
		GameNode * currentDestination;

		bool validPath; // false if invalid path

		GameNode * popCurrentConnection();
		bool isComplete();
	};
}