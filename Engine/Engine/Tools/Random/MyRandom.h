#pragma once

#include <ExportHeader.h>

namespace Random {
	ENGINE_SHARED int      Int(int low, int high);
	ENGINE_SHARED int      Sign();
	ENGINE_SHARED bool     Bool(int weightFalse = 1);
	ENGINE_SHARED float    Float();
	ENGINE_SHARED float    Float(float low, float high);
};