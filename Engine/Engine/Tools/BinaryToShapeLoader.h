#pragma once
#pragma warning(disable: 4201)
#pragma warning(push)
#include <ShapeData.h>
#pragma warning(pop)
#include <ExportHeader.h>
#include <Engine\unsigned.h>

typedef char myByte;

class ENGINE_SHARED BinaryToShapeLoader {
public:
	static Neumont::ShapeData loadFromFile(const char * filePath);
	static Neumont::ShapeData loadFromBinary(myByte * byteData);
};