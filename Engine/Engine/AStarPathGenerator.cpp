#include "AStarPathGenerator.h"


namespace AStar {
	Node * PathGenerator::convertToNode(GameNode * gNode) {
		uint id = gNode - gameNodes;
		if(pathingNodes[id].node == nullptr) {
			pathingNodes[id].init(glm::length(end->pos - gNode->pos),gNode);
		}
		return &pathingNodes[id];
	}

	//inits Node data and returns if valid Node
	void PathGenerator::processNode(Node * toProcess, Node * parentNode, float connectionCost) {
		if(toProcess->parent != nullptr)
		{
			Node possibleReplacement = toProcess->clone();
			possibleReplacement.setParent(parentNode,connectionCost);


			if(toProcess->isCheaper(&possibleReplacement)) {
				return; // nothing to do here
			} else {
				toProcess->setParent(parentNode,connectionCost); // also calculates
			}
		} else {
			toProcess->setParent(parentNode,connectionCost); // also calcuates
		}
		openList.push_back(toProcess);
	}

	Node * PathGenerator::popCheapestNode() {
		int cheapestId = -1;
		for (uint i = 0; i < openList.size(); i++)
		{
			if(cheapestId<0 && openList[cheapestId]->estimatedTotalCost < openList[i]->estimatedTotalCost) {
				cheapestId = i;
			}
		}

		Node * ret = openList[cheapestId];
		openList.erase(openList.begin() + cheapestId);

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
	//generates and returns path
	Path PathGenerator::getPath(GameNode * start, GameNode * end) {
		this->start = start;
		this->end = end;
		//init open list
		openList.clear();
		openList.push_back(convertToNode(start));

		while(openList.size() > 0) {
			Node * processingParent = popCheapestNode(); // removes nodes for open
				
			//if end is found
			if(processingParent->node == end) {
				return genPath(processingParent);
			}
			//process connections
			for (int i = 0; i < processingParent->node->numOfConnections; i++)
			{
				Node * currentNode = convertToNode(processingParent->node->connections[i].to);
				processNode(currentNode,processingParent, processingParent->node->connections[i].cost);
			}
		}
		//invalid path
		Path ret;
		ret.validPath = false;
		return ret;
	}
}