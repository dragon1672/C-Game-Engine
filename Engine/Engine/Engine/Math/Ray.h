#pragma once

#include <glm\glm.hpp>
#include <ExportHeader.h>
#include <Engine\Tools\Camera.h>

struct ENGINE_SHARED Ray {
	glm::vec3 direction;
	glm::vec3 origin;
	
	void init(glm::vec2& mousePos, int width, int height, glm::mat4& viewAndPerTransform, Camera& myCam) {
		float x = (2.0f*mousePos.x)/width - 1.0f;
		float y = 1.0f - (2.0f* mousePos.y)/height;
		float z = -1.0f;

		glm::mat4x4 undoCam = glm::inverse(myCam.getWorld2View());
		glm::vec4 temp = glm::inverse(viewAndPerTransform * undoCam) * glm::vec4(x,y,z,0.0);
	
		this->direction = glm::normalize(glm::vec3(undoCam * glm::vec4(temp.x,temp.y,z,0.0)));
		this->origin = myCam.getPos();
	}
};