#include "Mesh.h"

void Mesh::updateMinAndMax()
{
	for (uint i = 0; i < verts.size(); i++) {
		min.x = i==0 || verts[i].pos.x < min.x ? verts[i].pos.x : min.x;
		min.x = i==0 || verts[i].pos.y < min.y ? verts[i].pos.y : min.y;
		max.x = i==0 || verts[i].pos.x < max.x ? verts[i].pos.x : max.x;
		max.x = i==0 || verts[i].pos.y < max.y ? verts[i].pos.y : max.y;
	}
}

void Mesh::passToHardware()
{
	geo.init(sizeof(Vert),(const void*)&verts[0],verts.size(),&indices[0],indices.size(),3);
	geo.addStreamedParameters(Vert().getAtribs(),Vert().getNumOfAtribs());
}

void Mesh::updateTangents()
{
	glm::vec3 * tan1 = new glm::vec3[verts.size()];// * 2];
	//glm::vec3 * tan2 = tan1 + obj.numVerts;
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
		//obj.verts[i].color.w = (glm::dot(glm::cross(n, t), tan2[i]) < 0.0F) ? -1.0F : 1.0F;
	}
	delete[] tan1;
}
