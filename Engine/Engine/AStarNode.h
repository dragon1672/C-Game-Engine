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

		void init(float heuristicValue, GameNode * node, Node * parent=nullptr) {
			this->parent = parent;
			this->node = node;
			this->heuristicValue = heuristicValue;
			calculateValuesFromParent();
		}

		void setParent(Node * parent, float connectionCost) {
			this->parent = parent;
			calculateValuesFromParent(connectionCost);
		}

		void calculateValuesFromParent(float cost) {
			costSoFar = (parent == nullptr)? parent->costSoFar + cost : 0;
			estimatedTotalCost = costSoFar + heuristicValue;
		}
		bool isCheaper(Node * that) {
			return this->estimatedTotalCost < that->estimatedTotalCost;
		}
		//to be used in comparing a new guy
		Node clone() {
			return Node(heuristicValue,node,parent);
		}
	};
}