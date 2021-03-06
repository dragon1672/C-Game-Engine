#include <gl/glew.h>
#include "Mesh.h"
#include <Engine\Tools\Random\MyRandom.h>
#include <glm/gtx/transform.hpp>
#include <Engine/Tools/MatrixInfo.h>
#include <Engine/IO/Stream.h>

namespace {
	glm::vec3 operator*(const glm::mat4& mat, const glm::vec3& vec) {
		return glm::vec3(mat * glm::vec4(vec,1));
	}

	float max_withABS(float a, float b) {
		a = abs(a);	b = abs(b);
		return a > b ? a : b;
	}
	STREAMER_FOR_TYPE(,,Vert);
}

void Mesh::updateMinAndMax()
{
	for (uint i = 0; i < verts.size(); i++) {
		min.x = i==0 || verts[i].pos.x < min.x ? verts[i].pos.x : min.x;
		min.x = i==0 || verts[i].pos.y < min.y ? verts[i].pos.y : min.y;
		max.x = i==0 || verts[i].pos.x < max.x ? verts[i].pos.x : max.x;
		max.x = i==0 || verts[i].pos.y < max.y ? verts[i].pos.y : max.y;
	}
}

void Mesh::updateTangents()
{
	glm::vec3 * tan1 = new glm::vec3[verts.size()];// * 2];
	//glm::vec3 * tan2 = tan1 + verts.size();
	//ZeroMemory(tan1, vertexCount * sizeof(Vector3D) * 2);
	for (uint i = 0; i < indices.size()/3; i++)
	{
		long i1 = indices[0 + i*3];
		long i2 = indices[1 + i*3];
		long i3 = indices[2 + i*3];

		Vert& v1 = verts[i1];
		Vert& v2 = verts[i2];
		Vert& v3 = verts[i3];

		float x1 = v2.pos.x - v1.pos.x;
		float x2 = v3.pos.x - v1.pos.x;
		float y1 = v2.pos.y - v1.pos.y;
		float y2 = v3.pos.y - v1.pos.y;
		float z1 = v2.pos.z - v1.pos.z;
		float z2 = v3.pos.z - v1.pos.z;

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
	for (uint i = 0; i < verts.size(); i++)
	{
		glm::vec3& n = verts[i].norm;
		glm::vec3& t = tan1[i];
		// Gram-Schmidt orthogonalized
		verts[i].tan = glm::vec4(glm::normalize((t - n * glm::dot(n, t))),0);

		// Calculate handedness
		//verts[i].tan.w = (glm::dot(glm::cross(n, t), tan2[i]) < 0.0F) ? -1.0F : 1.0F;
	}
	delete[] tan1;
}

void Mesh::noNegY() {
	float min = 0;
	float max = 0;
	for (uint i = 0; i < verts.size(); i++) {
		glm::vec3 checking = verts[i].pos;
		min = checking.y < min ? checking.y : min;
		max = checking.y > max ? checking.y : max;
	}
	if(min<0) {
		float bumVal = -min;
		for (uint i = 0; i < verts.size(); i++) {
			verts[i].pos.y += bumVal;
		}
	}
}


void Mesh::scaleToRange(float xBound, float yBound, float zBound) {
	glm::vec3 min;
	glm::vec3 max;
	for (uint i = 0; i < verts.size(); i++) {
		glm::vec3 checking = verts[i].pos;
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
	for (uint i = 0; i < verts.size(); i++) {
		verts[i].pos = scale * verts[i].pos;
	}
}
void Mesh::setRandomColor(int everyThisNumOfPoints) {
	for (uint i = 0; i < verts.size(); i++) {
		if(i % everyThisNumOfPoints == 0) {
			float r = Random::Float(0,1);
			float g = Random::Float(0,1);
			float b = Random::Float(0,1);
			//float a = Random::randomFloat(0,1);
			verts[i].col = glm::vec4(r,g,b,1);
		}
	}
}
void Mesh::setColor(glm::vec4 toSet, int everyThisNumOfPoints) {
	for (uint i = 0; i < verts.size(); i++) {
		if(i % everyThisNumOfPoints == 0) {
			verts[i].col = toSet;
		}
	}
}
void Mesh::initUVData() {
	int size = (int)sqrt(verts.size());
	float divisor = (float)size-1;
	for(unsigned int i = 0; i<verts.size(); i++)
	{
		int row = (i/size);
		int column = (i%size);
		verts[i].uv = glm::vec2(row/divisor, column/divisor);
	}
}
void Mesh::scale(float scale) {
	for(unsigned int i = 0; i<verts.size(); i++) {
		verts[i].pos *= scale;
	}
}

void Mesh::scale(float x,float y, float z)
{
	scale(glm::vec3(x,y,z));
}

void Mesh::scale(glm::vec3 scale)
{
	MatrixInfo trans;
	trans.scale = scale;
	generalTransform(trans);
}

void Mesh::rotate(float x, float y, float z) {
	glm::mat3 rot = glm::mat3(
		glm::rotate(x,glm::vec3(1,0,0))
		* glm::rotate(y,glm::vec3(0,1,0))
		* glm::rotate(z,glm::vec3(0,0,1))
		);
	for(unsigned int i = 0; i<verts.size(); i++)
	{
		verts[i].pos  = rot * verts[i].pos;
		verts[i].norm = rot * verts[i].norm;
	}
}

void Mesh::PassDownToHardWare()
{
	updateTangents();
	updateMinAndMax();
	geo.init(&verts[0],verts.size(),&indices[0],indices.size(),drawStyle);
	geo.addStreamedParameters<Vert>(Vert::getAtribs(),Vert::getNumOfAtribs());
	inHardware = true;
}

Mesh::Mesh(std::string name)
	: Resource_CRTP(name), inHardware(false)
{
	drawStyle = GL_TRIANGLES;
}

void Mesh::paint()
{
	if(!inHardware) PassDownToHardWare();
	GeometryInfo& toDraw = geo;
	glBindVertexArray(toDraw.vertexArrayObjectID);
	glBindBuffer(toDraw.bufferInformation.bufferID,GL_ARRAY_BUFFER);
	glBindBuffer(toDraw.bufferInformation.bufferID,GL_ELEMENT_ARRAY_BUFFER);
	glDrawElements(toDraw.indexingMode,toDraw.numIndices,GL_UNSIGNED_INT,(void*)toDraw.indicesOffset());
}

void Mesh::generalTransform(MatrixInfo& transform)
{
	generalTransform(transform.getCompleteTransform());
}

void Mesh::generalTransform(MatrixInfo * transform)
{
	generalTransform(transform->getCompleteTransform());
}

void Mesh::generalTransform(glm::mat4 transform)
{
	for (uint i = 0; i < verts.size(); i++) {
		verts[i].pos = transform * verts[i].pos;
	}
}

void Mesh::translate(float x, float y, float z)
{
	translate(glm::vec3(x,y,z));
}

void Mesh::translate(glm::vec3 pos)
{
	MatrixInfo trans;
	trans.pos = pos;
	generalTransform(trans);
}

bool Mesh::isValid()
{
	return verts.size() > 0 && indices.size() > 0;
}

std::vector<std::string> Mesh::getErrors()
{
	std::vector<std::string> ret;
	if(verts.size()   == 0) ret.push_back("No Verts in Mesh");
	if(indices.size() == 0) ret.push_back("No Indices in Mesh");
	return ret;
}

void Mesh::ChildSave(Stream& s)
{
	s << drawStyle << verts << indices;
}

void Mesh::ChildLoad(Stream& s)
{
	s >> drawStyle >> verts >> indices;
	inHardware = false;
}

void Mesh::shutdown()
{
	inHardware = false;
}

bool Mesh::equals(Mesh& that) const
{
	if(drawStyle != that.drawStyle) return false;
	if(verts.size() != that.verts.size()) return false;
	if(indices.size() != that.indices.size()) return false;
	for (uint i = 0; i < verts.size();   i++) { if(verts[i]   != that.verts[i])   return false; }
	for (uint i = 0; i < indices.size(); i++) { if(indices[i] != that.indices[i]) return false; }
	return true;
}
