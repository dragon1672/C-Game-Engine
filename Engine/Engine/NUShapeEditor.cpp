#pragma warning(disable: 4201)
#pragma warning(push)
#include "NUShapeEditor.h"
#include <ShapeData.h>
#pragma warning(pop)
#include "MyRandom.h"
#include <glm/gtx/transform.hpp>

glm::vec3 differentMatrixMult(glm::mat4 mat, glm::vec3 vec) {
	return glm::vec3(mat * glm::vec4(vec,1));
}

Neumont::ShapeData NUShapeEditor::fixTeaPotNormals(Neumont::ShapeData& obj) {
	// ???
	return obj;
}
Neumont::ShapeData NUShapeEditor::noNegY(Neumont::ShapeData& obj) {
	float min = 0;
	float max = 0;
	for (uint i = 0; i < obj.numVerts; i++) {
		glm::vec3 checking = obj.verts[i].position;
		min = checking.y < min ? checking.y : min;
		max = checking.y > max ? checking.y : max;
	}
	if(min<0) {
		float bumVal = -min;
		for (uint i = 0; i < obj.numVerts; i++) {
			obj.verts[i].position.y += bumVal;
		}
	}
	return obj;
}

/*
float abs(float val) {
	return val < 0 ? - val : val;
}
//*/

float max_withABS(float a, float b) {
	a = abs(a);	b = abs(b);
	return a > b ? a : b;
}

Neumont::ShapeData NUShapeEditor::scaleToRange(Neumont::ShapeData& obj, float xBound, float yBound, float zBound) {
	glm::vec3 min;
	glm::vec3 max;
	for (uint i = 0; i < obj.numVerts; i++) {
		glm::vec3 checking = obj.verts[i].position;
		for (int i = 0; i < 3; i++)
		{
			min[i] = checking[i] < min[i] ? checking[i] : min[i];
			max[i] = checking[i] > max[i] ? checking[i] : max[i];
		}
	}
	float xScale = xBound / max_withABS(max.x, min.x);	xScale = xScale < 1 ? xScale : 1;
	float yScale = yBound / max_withABS(max.y, min.y);	yScale = yScale < 1 ? yScale : 1;
	float zScale = zBound / max_withABS(max.z, min.z);	zScale = zScale < 1 ? zScale : 1;
	glm::mat4 scale = glm::scale(xScale,yScale,zScale);
	for (uint i = 0; i < obj.numVerts; i++) {
		obj.verts[i].position = differentMatrixMult(scale,obj.verts[i].position);
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::setModColor(Neumont::ShapeData& obj, int mod) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % mod == 0) {
			float r = Random::randomFloat(0,1);
			float g = Random::randomFloat(0,1);
			float b = Random::randomFloat(0,1);
			//float a = Random::randomFloat(0,1);
			obj.verts[i].color = glm::vec4(r,g,b,1);
		}
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::setColor(glm::vec4& toSet, Neumont::ShapeData& obj, int mod) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % mod == 0) {
			obj.verts[i].color = toSet;
		}
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::initUVData(Neumont::ShapeData& obj) {
	int size = (int)sqrt(obj.numVerts);
	float divisor = (float)size-1;
	for(unsigned int i = 0; i<obj.numVerts; i++)
	{
		int row = (i/size);
		int column = (i%size);
		obj.verts[i].uv = glm::vec2(row/divisor, column/divisor);
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::scale(Neumont::ShapeData& obj, float scale) {
	for(unsigned int i = 0; i<obj.numVerts; i++)
	{
		obj.verts[i].position *= scale;
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::rotate(Neumont::ShapeData& obj, float x, float y, float z) {
	glm::mat3 rot = glm::mat3(
					glm::rotate(x,glm::vec3(1,0,0))
				  * glm::rotate(y,glm::vec3(0,1,0))
				  * glm::rotate(z,glm::vec3(0,0,1))
				  );
	for(unsigned int i = 0; i<obj.numVerts; i++)
	{
		obj.verts[i].position = rot * obj.verts[i].position;
		obj.verts[i].normal   = rot * obj.verts[i].normal;
	}
	return obj;
}