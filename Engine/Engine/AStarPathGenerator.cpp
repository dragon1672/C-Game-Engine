#include "AStarPathGenerator.h"


namespace AStar {
	Node PathGenerator::convertToNode(GameNode * gNode) {
		for (uint i = 0; i < openList.size(); i++)
		{
			if(openList[i].node == gNode) {
				return openList[i];
			}
		}
		return Node(glm::length(end->pos - gNode->pos),gNode);
	}

	//inits Node data and returns if valid Node
	void PathGenerator::processNode(Node& toProcess, Node& parentNode, float connectionCost) {
		if(toProcess.parent != nullptr)
		{
			Node possibleReplacement = toProcess.clone();
			possibleReplacement.setParent(&parentNode,connectionCost);


			if(toProcess.isCheaper(&possibleReplacement)) {
				return; // nothing to do here
			} else {
				toProcess.setParent(&parentNode,connectionCost); // also calculates
			}
		} else {
			toProcess.setParent(&parentNode,connectionCost); // also calcuates
		}
		openList.push_back(toProcess);
	}

	Node PathGenerator::popCheapestNode() {
		Node * current = nullptr;
		for (uint i = 0; i < openList.size(); i++)
		{
			if(current==nullptr && current->estimatedTotalCost < openList[i].estimatedTotalCost) {
				current = &openList[i];
			}
		}

		Node ret = *current;
			
		int nodeID = current - &openList[0];
		openList.erase(openList.begin() + nodeID);

		return ret;
	}
	Path PathGenerator::genPath(Node * endSeed) {
		Path ret;
		ret.validPath = true;
		Node * currentNode = endSeed;
		do {
			ret.positions.push_back(currentNode->node->pos);
		} while(currentNode->parent != nullptr);
		return ret;
	}
	void PathGenerator::init(GameNode * start, GameNode * end, GameNode * nodes, uint numOfGameNodes) {
		this->start = start;
		this->end = end;
		this->gameNodes = nodes;
		this->numOfGameNodes = numOfGameNodes;
		//init open list
		openList.push_back(convertToNode(start));
	};
	//generates and returns path
	Path PathGenerator::getPath() {
		while(openList.size() > 0) {
			Node processingParent = popCheapestNode(); // removes nodes for open
				
			//if end is found
			if(processingParent.node == end) {
				return genPath(&processingParent);
			}
			//process connections
			for (int i = 0; i < processingParent.node->numOfConnections; i++)
			{
				Node currentNode = convertToNode(processingParent.node->connections[i].to);
				processNode(currentNode,processingParent, processingParent.node->connections[i].cost);
			}
		}
		//invalid path
		Path ret;
		ret.validPath = false;
		return ret;
	}
}