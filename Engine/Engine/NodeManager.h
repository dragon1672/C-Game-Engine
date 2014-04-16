#pragma once

#include <vector>
#include "EditorNode.h"
#include "Ray.h"
#include "ExportHeader.h"
#include "EditorNodeConnection.h"
#include "uint.h"

#define UnSelectedColor glm::vec4(0,0,1,1)
#define SelectedColor glm::vec4(1,0,0,1)
#define ConnectedNodeColor glm::vec4(0,1,0,1)

class ENGINE_SHARED NodeManager {
public:
	std::vector<EditorNode *> nodes;

	EditorNode * currentSelectedNode;
	EditorNode * getNextNode();
	DebugShapeManager * debugShapes;
public:
	inline void init(DebugShapeManager * debugShapes) {
		this->debugShapes = debugShapes;
		currentSelectedNode = nullptr;
	}

	void addNodeOnPlane(Ray& ray, glm::vec3 planePos,glm::vec3 planeNorm);
	EditorNode * getNodeClicked(Ray& click);
	void selectNode(EditorNode * toSelect);
	void deleteNode(EditorNode * toDel);
	void deleteNodeSelectedNode();
	void setAllNodeColors(glm::vec4& colorToSet);
	void setAllConnections(bool state = false);
	void activateAllConnections();
	void addOrSelectClick(Ray& click);
	void connectClick(Ray& click);
};