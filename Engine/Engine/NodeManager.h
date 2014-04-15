#pragma once

#include <vector>
#include "EditorNode.h"
#include "Ray.h"
#include "ExportHeader.h"
#include "EditorNodeConnection.h"

typedef unsigned int uint;

#define UnSelectedColor glm::vec4(0,0,1,1)
#define SelectedColor glm::vec4(1,0,0,1)
#define ConnectedNodeColor glm::vec4(0,1,0,1)

class ENGINE_SHARED NodeManager {
public:
	struct ENGINE_SHARED NodeSelection {
		EditorNode* nodes[10];
		uint numOfNodes;
	};
public:
	EditorNode nodes[100];
	uint numOfNodes;
	std::vector<EditorNodeConnection> connections;

	EditorNode * currentSelectedNode;
	DebugShapeManager * debugShapes;
	EditorNode * getNextNode();
public:
	inline void init(DebugShapeManager * debugShapes) {
		numOfNodes = 0;
		this->debugShapes = debugShapes;
		currentSelectedNode = nullptr;
	}

	void addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm);
	NodeSelection getNodesSelected(Ray& click);
	EditorNode * getNodeClicked(Ray& click);
	void selectNode(EditorNode * toSelect);
	void cleanupNodes();
	void deleteNode(EditorNode * toDel);
	void deleteNodeSelectedNode();
	void setAllNodeColors(glm::vec4& colorToSet);
	void setAllConnections(bool state = false);
	void activateAllConnections();
	void activateConnections(EditorNode * startWith);
	void addOrSelectClick(Ray& click);
	void connectClick(Ray& click);
	bool validConnections(EditorNodeConnection& toAdd);
};