#pragma once
#pragma warning(disable: 4201)
#pragma warning(push)
#include <ShapeData.h>
#pragma warning(pop)
#include "ExportHeader.h"

class ENGINE_SHARED BinaryToShapeLoader {
public:
	static Neumont::ShapeData loadFromFile(const char * filePath);
};