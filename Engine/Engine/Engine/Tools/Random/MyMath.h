#pragma once

#include <ExportHeader.h>
#include <Engine\Math\Vector 2.h>
#include <Engine\Tools\Random\MyRandom.h>

namespace Random {
	namespace myRand {
		ENGINE_SHARED Vector2D randomUnitVector();
		ENGINE_SHARED Vector2D randomFloatVectorInBox(float width, float height);
		ENGINE_SHARED Vector2D randomIntVectorInBox  (int   width, int   height);
		ENGINE_SHARED Vector2D randomFloatVector(float low, float high);
		ENGINE_SHARED Vector2D randomIntVector  (int   low, int   high);
	}
};