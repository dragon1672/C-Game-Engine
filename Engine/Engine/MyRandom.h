#pragma once
#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include "ExportHeader.h"

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
	ENGINE_SHARED void     init();
};

#endif//MY_RANDOM_H
