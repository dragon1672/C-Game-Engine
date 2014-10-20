#pragma once

#include <vector>
#include <Engine/Systems/Resources/Dependencies/Vert.h>
#include <Engine/TypeDefs.h>
#include <ShapeData.h>
#include <Engine/Systems/Resources/Dependencies/GeometryInfo.h>
#include <ExportHeader.h>
#include <Engine\Systems\Resource.h>

class ENGINE_SHARED Mesh : public Resource {
	GeometryInfo geo;
	glm::vec3 min;
	glm::vec3 max;
public:
	Mesh();
	Mesh(const char * name);
	std::vector<Vert> verts;
	std::vector<uint> indices;
	inline glm::vec3 Min() const { return min; }
	inline glm::vec3 Max() const { return max; }
	void updateMinAndMax();
	void updateTangents();
	//editing
	void noNegY();
	void scaleToRange(float xBound=1, float yBound=1, float zBound=1);
	void setRandomColor(int everyThisNumOfPoints=1);
	void setColor(glm::vec4 toSet, int everyThisNumOfPoints = 1);
	void initUVData();
	void scale(float scale);
	void rotate(float x, float y, float z);


	virtual void PassDownToHardWare();

};