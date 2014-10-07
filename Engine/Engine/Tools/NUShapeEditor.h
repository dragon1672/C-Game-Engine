#pragma once

#pragma warning(disable: 4201)
#pragma warning(push)
#include <ShapeData.h>
#pragma warning(pop)
#include <ExportHeader.h>


class ENGINE_SHARED NUShapeEditor {
public:
	static Neumont::ShapeData noNegY(Neumont::ShapeData& obj);
	static Neumont::ShapeData scaleToRange(Neumont::ShapeData& obj, float xBound=1, float yBound=1, float zBound=1);
	static Neumont::ShapeData setRandomColor(Neumont::ShapeData& obj, int everyThisNumOfPoints=1);
	static Neumont::ShapeData setColor(glm::vec4& toSet, Neumont::ShapeData& obj, int everyThisNumOfPoints = 1);
	static Neumont::ShapeData initUVData(Neumont::ShapeData& obj);
	static Neumont::ShapeData scale(Neumont::ShapeData& obj, float scale);
	static Neumont::ShapeData rotate(Neumont::ShapeData& obj, float x, float y, float z);
	static Neumont::ShapeData overrideColorWithTanNormals(Neumont::ShapeData&obj);
};