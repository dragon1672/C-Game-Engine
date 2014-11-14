#pragma once

#include <vector>
#include <Engine/Systems/Resources/Dependencies/Vert.h>
#include <Engine/TypeDefs.h>
#include <ShapeData.h>
#include <Engine/Systems/Resources/Dependencies/GeometryInfo.h>
#include <ExportHeader.h>
#include <Engine\Systems\Resource.h>

class MatrixInfo;

class ENGINE_SHARED Mesh : public Resource {
	GeometryInfo geo;
	glm::vec3 min;
	glm::vec3 max;
	bool inHardware;
public:
	int drawStyle;
	Mesh(std::string name="");
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
	void scale(float x,float y, float z);
	void scale(glm::vec3 scale);
	void translate(float x, float y, float z);
	void translate(glm::vec3 pos);
	void rotate(float x, float y, float z);
	void generalTransform(glm::mat4 transform);
	void generalTransform(MatrixInfo * transform);
	void generalTransform(MatrixInfo& transform);


	virtual void PassDownToHardWare();
	void paint();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

};