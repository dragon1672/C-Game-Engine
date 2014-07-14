#pragma warning(disable: 4201)
#pragma warning(push)
#include <Engine\Tools\NUShapeEditor.h>
#include <ShapeData.h>
#pragma warning(pop)
#include <Engine\Tools\Random\MyRandom.h>
#include <glm/gtx/transform.hpp>

glm::vec3 differentMatrixMult(glm::mat4 mat, glm::vec3 vec) {
	return glm::vec3(mat * glm::vec4(vec,1));
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
Neumont::ShapeData NUShapeEditor::setRandomColor(Neumont::ShapeData& obj, int everyThisNumOfPoints) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % everyThisNumOfPoints == 0) {
			float r = Random::randomFloat(0,1);
			float g = Random::randomFloat(0,1);
			float b = Random::randomFloat(0,1);
			//float a = Random::randomFloat(0,1);
			obj.verts[i].color = glm::vec4(r,g,b,1);
		}
	}
	return obj;
}
Neumont::ShapeData NUShapeEditor::setColor(glm::vec4& toSet, Neumont::ShapeData& obj, int everyThisNumOfPoints) {
	for (uint i = 0; i < obj.numVerts; i++) {
		if(i % everyThisNumOfPoints == 0) {
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
/*
#include "Vector4D.h"
struct Triangle
{
 unsigned short index[3];
};
void CalculateTangentArray(long vertexCount, const Point3D *vertex, const Vector3D *normal,
 const Point2D *texcoord, long triangleCount, const Triangle *triangle, Vector4D *tangent)
{
 Vector3D *tan1 = new Vector3D[vertexCount * 2];
 Vector3D *tan2 = tan1 + vertexCount;
 ZeroMemory(tan1, vertexCount * sizeof(Vector3D) * 2);
 
 for (long a = 0; a < triangleCount; a++)
 {
 long i1 = triangle->index[0];
 long i2 = triangle->index[1];
 long i3 = triangle->index[2];
 
 const Point3D& v1 = vertex[i1];
 const Point3D& v2 = vertex[i2];
 const Point3D& v3 = vertex[i3];
 
 const Point2D& w1 = texcoord[i1];
 const Point2D& w2 = texcoord[i2];
 const Point2D& w3 = texcoord[i3];
 
 float x1 = v2.x - v1.x;
 float x2 = v3.x - v1.x;
 float y1 = v2.y - v1.y;
 float y2 = v3.y - v1.y;
 float z1 = v2.z - v1.z;
 float z2 = v3.z - v1.z;
 
 float s1 = w2.x - w1.x;
 float s2 = w3.x - w1.x;
 float t1 = w2.y - w1.y;
 float t2 = w3.y - w1.y;
 
 float r = 1.0F / (s1 * t2 - s2 * t1);
 Vector3D sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r,
 (t2 * z1 - t1 * z2) * r);
 Vector3D tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r,
 (s1 * z2 - s2 * z1) * r);
 
 tan1[i1] += sdir;
 tan1[i2] += sdir;
 tan1[i3] += sdir;
 
 tan2[i1] += tdir;
 tan2[i2] += tdir;
 tan2[i3] += tdir;
 
 triangle++;
 }
 
 for (long a = 0; a < vertexCount; a++)
 {
 const Vector3D& n = normal[a];
 const Vector3D& t = tan1[a];
 
 // Gram-Schmidt orthogonalize
 tangent[a] = (t - n * Dot(n, t)).Normalize();
 
 // Calculate handedness
 tangent[a].w = (Dot(Cross(n, t), tan2[a]) < 0.0F) ? -1.0F : 1.0F;
 }
 
 delete[] tan1;
}

//*/
Neumont::ShapeData NUShapeEditor::overrideColorWithTanNormals(Neumont::ShapeData&obj) {
	glm::vec3 * tan1 = new glm::vec3[obj.numVerts];// * 2];
	//glm::vec3 * tan2 = tan1 + obj.numVerts;
	//ZeroMemory(tan1, vertexCount * sizeof(Vector3D) * 2);
	for (int i = 0; i < obj.numIndices/3; i++)
	{
		long i1 = obj.indices[0 + i*3];
		long i2 = obj.indices[1 + i*3];
		long i3 = obj.indices[2 + i*3];
		
		Neumont::Vertex& v1 = obj.verts[i1];
		Neumont::Vertex& v2 = obj.verts[i2];
		Neumont::Vertex& v3 = obj.verts[i3];
		
		float x1 = v2.position.x - v1.position.x;
		float x2 = v3.position.x - v1.position.x;
		float y1 = v2.position.y - v1.position.y;
		float y2 = v3.position.y - v1.position.y;
		float z1 = v2.position.z - v1.position.z;
		float z2 = v3.position.z - v1.position.z;
 
		float s1 = v2.uv.x - v1.uv.x;
		float s2 = v3.uv.x - v1.uv.x;
		float t1 = v2.uv.y - v1.uv.y;

		float t2 = v3.uv.y - v1.uv.y;

		float r = 1.0f / (s1 * t2 - s2 * t1);
		glm::vec3 sdir( (t2 * x1 - t1 * x2) * r,     (t2 * y1 - t1 * y2) * r,      (t2 * z1 - t1 * z2) * r);
		glm::vec3 tdir( (s1 * x2 - s2 * x1) * r,     (s1 * y2 - s2 * y1) * r,      (s1 * z2 - s2 * z1) * r);
		
		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;
 
		//tan2[i1] += tdir;
		//tan2[i2] += tdir;
		//tan2[i3] += tdir;

	}
	for (int i = 0; i < obj.numVerts; i++)
	{
		glm::vec3& n = obj.verts[i].normal;
		glm::vec3& t = tan1[i];
		// Gram-Schmidt orthogonalize
		obj.verts[i].color = glm::vec4(glm::normalize((t - n * glm::dot(n, t))),0);

		// Calculate handedness
		//obj.verts[i].color.w = (glm::dot(glm::cross(n, t), tan2[i]) < 0.0F) ? -1.0F : 1.0F;
	}
	delete[] tan1;
	return obj;
}