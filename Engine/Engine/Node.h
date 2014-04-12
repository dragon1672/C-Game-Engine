#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <vector>
#include "ExportHeader.h"
#include "DebugShapeManager.h"
#include "Ray.h"

struct ENGINE_SHARED Node {
	static const int radius=1;
	DebugShapeManager::DebugShapeData * rednerable;
	glm::vec3 pos;
	bool isActive;

	bool doesRayHit(Ray& ray); //cheap
	bool tryIntersectionVector(Ray& ray, glm::vec3& ret); //uses sqrt
};