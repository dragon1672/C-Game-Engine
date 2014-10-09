#pragma once

#include <glm/glm.hpp>

#include "AutoAtrib.h"
#include <Vertex.h>

class Vert : public AutoAtrib {
public:
	Vert(){}
	Vert(Neumont::Vertex v) {
		pos =  v.position;
		col =  v.color;
		norm = v.normal;
		uv  =  v.uv;
	}
	int * getAtribs();
	int getNumOfAtribs();
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec3 norm;
	glm::vec3 tan;
	glm::vec2 uv;
};