#pragma once

#include <glm/glm.hpp>

#include <ExportHeader.h>

class ENGINE_SHARED	Vert {
public:
	glm::vec3 pos;
	glm::vec4 col;
	glm::vec3 norm;
	glm::vec4 tan;
	glm::vec2 uv;
	Vert(glm::vec3 pos = glm::vec3(0,0,0), glm::vec4 col = glm::vec4(1,1,1,1), glm::vec3 norm = glm::vec3(0,0,0), glm::vec4 tan = glm::vec4(0,0,0,0), glm::vec2 uv = glm::vec2(0,0)) :
		pos (pos ),
		col (col ),
		norm(norm),
		tan (tan ),
		uv  (uv  )
	{ }
	static int * getAtribs();
	static int getNumOfAtribs();
	static int stride();
};
inline bool operator==(const Vert& lhs, const Vert& rhs){
	if(lhs.pos  != rhs.pos ) return false;
	if(lhs.col  != rhs.col ) return false;
	if(lhs.norm != rhs.norm) return false;
	if(lhs.tan  != rhs.tan ) return false;
	if(lhs.uv   != rhs.uv  ) return false;
	return true;
}
inline bool operator!=(const Vert& lhs, const Vert& rhs){return !(lhs == rhs);}