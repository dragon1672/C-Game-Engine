#include "AStarNode.h"

namespace AStar {
	void Node::init(float heuristicValue, GameNode * node, Node * parent) {
		this->parent = parent;
		this->node = node;
		this->heuristicValue = heuristicValue;
		calculateValuesFromParent(0);
	}

	void Node::setParent(Node * parent, float connectionCost) {
		this->parent = parent;
		calculateValuesFromParent(connectionCost);
	}

	void Node::calculateValuesFromParent(float cost) {
		costSoFar = (parent != nullptr)? parent->costSoFar + cost : 0;
		estimatedTotalCost = costSoFar + heuristicValue;
	}
	bool Node::isCheaper(Node * that) {
		return this->estimatedTotalCost < that->estimatedTotalCost;
	}
	//to be used in comparing a new guy
	Node Node::clone() {
		return Node(heuristicValue,node,parent);
	}
}