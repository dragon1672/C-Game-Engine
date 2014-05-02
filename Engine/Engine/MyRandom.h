#pragma once
#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include "ExportHeader.h"
#include <glm\glm.hpp>

class Vector2D;

namespace Random {
	ENGINE_SHARED int      randomInt(int low, int high);
	ENGINE_SHARED int      randomSign();
	ENGINE_SHARED bool     randomBool();
	ENGINE_SHARED float    randomFloat();
	ENGINE_SHARED float    randomFloat(float low, float high);
	ENGINE_SHARED Vector2D randomUnitVector();
	ENGINE_SHARED Vector2D randomFloatVectorInBox(float width, float height);
	ENGINE_SHARED Vector2D randomIntVectorInBox  (int   width, int   height);
	ENGINE_SHARED Vector2D randomFloatVector(float low, float high);
	ENGINE_SHARED Vector2D randomIntVector  (int   low, int   high);
	namespace glmRand {
		ENGINE_SHARED glm::vec3 randomUnitVector();
		ENGINE_SHARED glm::vec3 randomFloatVectorInBoxRanged(float width, float height, float depth = 0);
		ENGINE_SHARED glm::vec3 randomFloatVectorInBox(float width, float height, float depth = 0);
		ENGINE_SHARED glm::vec3 randomIntVectorInBox  (int   width, int   height, int   depth = 0);
		ENGINE_SHARED glm::vec3 randomFloatVector(float low, float high);
		ENGINE_SHARED glm::vec3 randomIntVector  (int   low, int   high);
	}
	ENGINE_SHARED void     init(); // not required
};

#endif//MY_RANDOM_H
