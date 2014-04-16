#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <vector>
#include "ExportHeader.h"
#include "DebugShapeManager.h"
#include "Ray.h"
#include "uint.h"

struct EditorNodeConnection;

struct ENGINE_SHARED EditorNode {
	static const int radius=1;
	glm::vec3 pos;
	std::vector<EditorNodeConnection *> connections;


	DebugShapeManager::DebugShapeData * rednerable;
	void shutdown();
	void removeNode(EditorNode * idtoRemove);
	void activateConnections(glm::vec4 color);
	bool validConnection(EditorNode * toConnect);
	void setConnectionState(bool state);
	
	bool doesRayHit(Ray& ray); //cheap
	bool tryIntersectionVector(Ray& ray, glm::vec3& ret); //uses sqrt
};