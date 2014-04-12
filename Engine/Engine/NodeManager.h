#pragma once

#include <vector>
#include "Node.h"
#include "Ray.h"
#include "ExportHeader.h"

typedef unsigned int uint;

class ENGINE_SHARED NodeManager {
	Node nodes[100];
	uint numOfNodes;
	Node * currentSelectedNode;
	void addNodeOnPlane(glm::vec3& pos) {
		bool placed = false;
		for (uint i = 0; i < numOfNodes && !placed; i++)
		{
			if(!nodes[i].isActive) {
				nodes[i].isActive = true;
				nodes[i].pos = pos;
			}
		}
	}
	Node * getNodeClicked(Ray& click);
};