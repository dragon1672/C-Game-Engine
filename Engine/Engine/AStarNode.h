#pragma once

#include "GameNode.h"

namespace AStar {
	struct Node {
		Node * parent; // links to parent node
		GameNode * node;

		float currentTotalCost;
		float estimatedTotalCost;
		float heuristicValue;

		void init(float heuristicValue, GameNode * node, Node * parent=nullptr) {
			this->parent = parent;
			this->node = node;
			this->heuristicValue = heuristicValue;
		}

		void calculateValuesFromParent() {
			if(parent!=nullptr) {
				currentTotalCost = parent->currentTotalCost + heuristicValue;
			} else {
				currentTotalCost = 0;
				estimatedTotalCost = heuristicValue;
			}
		}
	};
}