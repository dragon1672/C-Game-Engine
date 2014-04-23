#pragma once

#include "GameNode.h"
#include "ExportHeader.h"

namespace AStar {
	struct ENGINE_SHARED Node {
		Node * parent; // links to parent node
		GameNode * node;

		float costSoFar;
		float estimatedTotalCost;
		float heuristicValue;

		Node() {}
		Node(float heuristicValue, GameNode * node, Node * parent=nullptr) {
			init(heuristicValue,node,parent);
		}

		void init(float heuristicValue, GameNode * node, Node * parent=nullptr);

		void setParent(Node * parent, float connectionCost);

		void calculateValuesFromParent(float cost);
		bool isCheaper(Node * that);
		//to be used in comparing a new guy
		Node clone();
	};
}