#pragma once

#include <glm/glm.hpp>

#include <ExportHeader.h>

class ENGINE_SHARED	Vert {
public:
	glm::vec3 pos;
	//glm::vec4 col;
	//glm::vec3 norm;
	//glm::vec4 tan;
	//glm::vec2 uv;
	Vert(glm::vec3 pos = glm::vec3(0,0,0), glm::vec4 col = glm::vec4(1,1,1,1), glm::vec3 norm = glm::vec3(0,0,0), glm::vec4 tan = glm::vec4(0,0,0,0), glm::vec2 uv = glm::vec2(0,0)) :
		pos (pos )
		//col (col ),
		//norm(norm),
		//tan (tan ),
		//uv  (uv  )
	{ }
	static int * getAtribs();
	static int getNumOfAtribs();
	static int stride();

};