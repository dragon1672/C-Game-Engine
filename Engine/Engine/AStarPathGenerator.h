#pragma once

#include "AStarPath.h"
#include "GameNode.h"
#include "GameNodeConnection.h"
#include "ExportHeader.h"

namespace AStar {
	class ENGINE_SHARED PathGenerator {
		GameNode * start;
		GameNode * end;
		GameNode * gameNodes;
		uint numOfGameNodes;
		std::vector<Node> openList;


		Node convertToNode(GameNode * gNode);

		//inits Node data and returns if valid Node
		void processNode(Node& toProcess, Node& parentNode, float connectionCost);

		Node popCheapestNode();
		Path genPath(Node * endSeed);
	public:
		void init(GameNode * start, GameNode * end, GameNode * nodes, uint numOfGameNodes);
		//generates and returns path
		Path getPath();
	};
}