#pragma once

#include <ExportHeader.h>
#include <glm\glm.hpp>

namespace Random {
	ENGINE_SHARED int      randomInt(int low, int high);
	ENGINE_SHARED int      randomSign();
	ENGINE_SHARED bool     randomBool(int weightFalse = 1);
	ENGINE_SHARED float    randomFloat();
	ENGINE_SHARED float    randomFloat(float low, float high);
};