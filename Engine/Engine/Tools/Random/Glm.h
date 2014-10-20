#pragma once

#include <Engine\Tools\Random\MyRandom.h>
#include <ExportHeader.h>
#include <glm\glm.hpp>

namespace Random {
	namespace glmRand {
		ENGINE_SHARED glm::vec3 UnitVector();
		ENGINE_SHARED glm::vec3 FloatVectorInBoxRanged(float width, float height, float depth = 0);
		ENGINE_SHARED glm::vec3 FloatVectorInBox(float width, float height, float depth = 0);
		ENGINE_SHARED glm::vec3 IntVectorInBox  (int   width, int   height, int   depth = 0);
		ENGINE_SHARED glm::vec3 FloatVector(float low, float high);
		ENGINE_SHARED glm::vec3 IntVector  (int   low, int   high);
	}
};