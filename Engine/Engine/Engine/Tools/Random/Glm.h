#pragma once

#include <ExportHeader.h>
#include <glm\glm.hpp>
#include <Engine\Tools\Random\MyRandom.h>

namespace Random {
	namespace glmRand {
		ENGINE_SHARED glm::vec3 randomUnitVector();
		ENGINE_SHARED glm::vec3 randomFloatVectorInBoxRanged(float width, float height, float depth = 0);
		ENGINE_SHARED glm::vec3 randomFloatVectorInBox(float width, float height, float depth = 0);
		ENGINE_SHARED glm::vec3 randomIntVectorInBox  (int   width, int   height, int   depth = 0);
		ENGINE_SHARED glm::vec3 randomFloatVector(float low, float high);
		ENGINE_SHARED glm::vec3 randomIntVector  (int   low, int   high);
	}
};