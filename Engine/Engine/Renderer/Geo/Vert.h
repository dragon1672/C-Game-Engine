#pragma once

#include <glm/glm.hpp>

#include "AutoAtrib.h"
#include <Vertex.h>

class Vert : public AutoAtrib {
public:
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec3 norm;
	glm::vec3 tan;
	glm::vec2 uv;
	Vert() : 
		pos(0,0,0),
		col(1,1,1,1),
		norm(0,0,0),
		tan(0,0,0),
		uv(0,0)
	{}
	Vert(Neumont::Vertex v) {
		pos =  v.position;
		col =  v.color;
		norm = v.normal;
		uv  =  v.uv;
	}
	int * getAtribs();
	int getNumOfAtribs();
};