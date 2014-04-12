#pragma once

#include <vector>
#include "Node.h"
#include "Ray.h"
#include "ExportHeader.h"
#include "NodeConnection.h"

typedef unsigned int uint;

class ENGINE_SHARED NodeManager {
public:
	static glm::vec4 UnSelectedColor;
	static glm::vec4 SelectedColor;
	static glm::vec4 ConnectedNodeColor;
	struct ENGINE_SHARED NodeSelection {
		Node* nodes[10];
		uint numOfNodes;
	};
public:
	Node nodes[100];
	uint numOfNodes;
	NodeConnection connections[100];
	uint numOfConnections;

	Node * currentSelectedNode;
	DebugShapeManager * debugShapes;
	Node * getNextNode();
public:
	inline void init(DebugShapeManager * debugShapes) {
		this->debugShapes = debugShapes;
	}

	void addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm);
	NodeSelection getNodesSelected(Ray& click);
	Node * getNodeClicked(Ray& click);
	void selectNode(Node * toSelect) {
		currentSelectedNode->rednerable->overrideColor = UnSelectedColor;
		currentSelectedNode = toSelect;
		currentSelectedNode->rednerable->overrideColor = SelectedColor;
	}
	void deleteNode(Node * toDel);
	void manageClick(Ray& click) {
		Node * selectedNode = getNodeClicked(click);
		if(selectedNode==nullptr) {
			addNodeOnPlane(click,glm::vec3(0,0,0),glm::vec3(0,1,0));
		} else {
			selectNode(selectedNode);
		}
	}
	/*
		hide all connections
		reset all node colors
		delete connects based off node
		activate connects based off from node
		activate all connections
		ensure that that renderable is only created on new node
		ensure that renderable display bool and node display bool are synced properly

		shift click will add connection, click selects/add new node
		switch interaction click to Lclick and cam to RClick
	//*/
};