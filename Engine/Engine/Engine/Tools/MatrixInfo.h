#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <ExportHeader.h>

class ENGINE_SHARED MatrixInfo {
private:
	glm::mat4 transform;
	glm::mat4 rotationMat;
	glm::mat4 translationMat;
	glm::mat4 scaleMat;
	
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 preTransform;
	glm::mat4 postTransform;

	MatrixInfo() : scale(1,1,1) {}

	glm::mat4& getTransform();// save this on in the Shader

	//gen short for generate, also return address that can ben sent to shader
	//warning these mats are updated so any changes will not stick
	glm::mat4&  genRotMat();
	glm::mat4&  genScaleMat();
	glm::mat4&  genTranslationMat();
	glm::mat4&  genCompleteTransform();

	//called by renderer in draw before passing uniforms to shader
	void updateMatrix();
};