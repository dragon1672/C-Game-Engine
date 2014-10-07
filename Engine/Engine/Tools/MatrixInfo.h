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

	//sets the x y and z to this scale
	void setScale(float xyz);

	glm::mat4& getTransform();// save this on in the Shader

	glm::mat4&  getRotMat();
	glm::mat4&  getScaleMat();
	glm::mat4&  getTranslationMat();
	glm::mat4&  getCompleteTransform();

	//called by renderer in draw before passing uniforms to shader
	void updateMatrix();
};