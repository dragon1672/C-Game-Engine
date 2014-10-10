#pragma once

#include <vector>
#include "Vert.h"
#include <Engine/unsigned.h>
#include <ShapeData.h>
#include <Engine/Renderer/Geo/GeometryInfo.h>

class Mesh {
	GeometryInfo geo;
public:
	Mesh() {}
	Mesh(Neumont::ShapeData& NU) {
		for (uint i = 0; i < NU.numVerts; i++)   { verts.push_back(Vert(NU.verts[i])); }
		for (uint i = 0; i < NU.numIndices; i++) { indices.push_back(NU.indices[i]);  }
	}
	std::vector<Vert> verts;
	std::vector<uint> indices;
	glm::vec3 min;
	glm::vec3 max;
	void updateMinAndMax();


	void passToHardware();

};