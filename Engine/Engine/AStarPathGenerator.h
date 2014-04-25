#pragma once

#include "AStarPath.h"
#include "GameNode.h"
#include "GameNodeConnection.h"
#include "ExportHeader.h"

namespace AStar {
	class ENGINE_SHARED PathGenerator {
		GameNode * gameNodes;
		uint numOfGameNodes;
		Node * pathingNodes;


		std::vector<Node *> openList;
		GameNode * start;
		GameNode * end;
		Node * convertToNode(GameNode * gNode);

		//inits Node data and returns if valid Node
		void processNode(Node * toProcess, Node * parentNode, float connectionCost);

		Node * popCheapestNode();
		Path genPath(Node * endSeed);
		void updateValues();
	public:
		void init(GameNode * nodes, uint numOfGameNodes);
		//generates and returns path
		Path getPath(GameNode * start, GameNode * end);
	};
}