#pragma once

#include <vector>
#include "EditorNode.h"
#include "Ray.h"
#include "ExportHeader.h"
#include "EditorNodeConnection.h"
#include "unsigned.h"
#include "GameNode.h"
#include "GameNodeConnection.h"
#include "AStarPath.h"

#define UnSelectedColor glm::vec4(0,0,1,1)
#define SelectedColor glm::vec4(1,0,0,1)
#define ConnectedNodeColor glm::vec4(0,1,0,1)

class ENGINE_SHARED NodeManager {
public:
	std::vector<EditorNode *> nodes;
	int numOfConnections; // used to make saving easier

private:
	EditorNode * currentSelectedNode;
	EditorNode * getNextNode();
	DebugShapeManager * debugShapes;
	uint getOffset(GameNode* startOfArray);
public:
	inline void init(DebugShapeManager * debugShapes) {
		this->debugShapes = debugShapes;
		currentSelectedNode = nullptr;
		numOfConnections = 0;
	}

	int getNodeId(EditorNode * toFind);
	void addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm);
	void addNode(glm::vec3 pos);
	EditorNode * getNodeClicked(Ray& click);
	EditorNode * findNode(GameNode * toFind, GameNode * startOfArray);
	EditorNode * findNode(GameNode* toFind);
	EditorNode * findNode(glm::vec3& pos);

	void selectNode(EditorNode * toSelect);
	void deleteNode(EditorNode * toDel);
	void deleteNodeSelectedNode();
	void deleteAll();
	void setAllNodeColors(glm::vec4& colorToSet);
	void setAllConnections(bool state = false);
	void activateAllConnections();
	void addOrSelectClick(Ray& click);
	void connectClick(Ray& click);
	void addConnection(uint fromID, uint toID);
	void addConnection(EditorNode * fromNode, EditorNode * toNode);

	void hilightPath(AStar::Path& lePath,glm::vec4& nextNodeColor, glm::vec4& finalNodeColor, glm::vec4& pathNodeColor);

	void importNodesAndConnections(GameNode * gameNodes, uint nodeCount);
	GameNode * exportToGameNode(int& numOfNodes);
};