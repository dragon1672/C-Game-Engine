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
		for (int i = 0; i < NU.numVerts; i++)   { verts.push_back(Vert(NU.verts[i])); }
		for (int i = 0; i < NU.numIndices; i++) { indicees.push_back(NU.indices[i]);  }
	}
	std::vector<Vert> verts;
	std::vector<uint> indicees;
	glm::vec3 min;
	glm::vec3 max;
	void updateMinAndMax() {
		for (int i = 0; i < verts.size(); i++) {
			min.x = i==0 || verts[i].pos.x < min.x ? verts[i].pos.x : min.x;
			min.x = i==0 || verts[i].pos.y < min.y ? verts[i].pos.y : min.y;
			max.x = i==0 || verts[i].pos.x < max.x ? verts[i].pos.x : max.x;
			max.x = i==0 || verts[i].pos.y < max.y ? verts[i].pos.y : max.y;
		}
	}


	void passToHardware() {
		geo.init(sizeof(Vert),&verts[0],verts.size(),&indicees[0],indicees.size(),3);
		int 
	}

};