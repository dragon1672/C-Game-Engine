#pragma once

#include <vector>
#include "Node.h"
#include "Ray.h"
#include "ExportHeader.h"
#include "NodeConnection.h"

typedef unsigned int uint;


#define UnSelectedColor glm::vec4(0,0,1,1)
#define SelectedColor glm::vec4(1,0,0,1)
#define ConnectedNodeColor glm::vec4(0,1,0,1)

class ENGINE_SHARED NodeManager {
public:
	struct ENGINE_SHARED NodeSelection {
		Node* nodes[10];
		uint numOfNodes;
	};
public:
	Node nodes[100];
	uint numOfNodes;
	std::vector<NodeConnection> connections;

	Node * currentSelectedNode;
	DebugShapeManager * debugShapes;
	Node * getNextNode();
public:
	inline void init(DebugShapeManager * debugShapes) {
		numOfNodes = 0;
		this->debugShapes = debugShapes;
	}

	void addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm);
	NodeSelection getNodesSelected(Ray& click);
	Node * getNodeClicked(Ray& click);
	void selectNode(Node * toSelect) {
		setAllConnections(false);
		setAllNodeColors(UnSelectedColor);
		currentSelectedNode = toSelect;
		currentSelectedNode->rednerable->overrideColor = SelectedColor;
		for (uint i = 0; i < connections.size(); i++)
		{
			if(connections[i].from == currentSelectedNode)
				connections[i].renderable -> overrideColor = ConnectedNodeColor;
		}
	}
	void deleteNode(Node * toDel) {
		//delete all connections
		for (uint i = 0; i < connections.size(); i++)
		{
			if(connections[i].from == toDel || connections[i].to == toDel) {
				connections[i].renderable->kill();
				connections.erase(connections.begin() + i);
				i--;
			}
		}
		toDel->isActive = false;
	}
	void setAllNodeColors(glm::vec4& colorToSet) {
		for (uint i = 0; i < numOfNodes; i++)
		{
			nodes[i].rednerable->overrideColor = colorToSet;
		}
	}
	void setAllConnections(bool state = false) {
		for (uint i = 0; i < connections.size(); i++)
		{
			connections[i].renderable->draw = state;
		}
	}
	void addOrSelectClick(Ray& click) {
		Node * selectedNode = getNodeClicked(click);
		if(selectedNode==nullptr) {
			addNodeOnPlane(click,glm::vec3(0,0,0),glm::vec3(0,1,0));
		} else {
			selectNode(selectedNode);
		}
	}
	void connectClick(Ray& click) {
		if(currentSelectedNode != nullptr) {
			Node * selectedNode = getNodeClicked(click);
			if(selectedNode!=nullptr) {
				NodeConnection toAdd;
				toAdd.from = currentSelectedNode;
				toAdd.to = selectedNode;
				glm::vec3 vectorPointer = selectedNode->pos - currentSelectedNode->pos;
				toAdd.renderable = debugShapes->addUnitVector(currentSelectedNode->pos,vectorPointer,glm::vec4(0,1,1,1));
				connections.push_back(toAdd);
			}
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