#include "MatrixInfo.h"
#include <glm\gtc\quaternion.hpp>

void MatrixInfo::updateMatrix() {
	transform = genCompleteTransform();
}
glm::mat4& MatrixInfo::getTransform()     { return transform;     } // save this on in the Shader

glm::mat4&  MatrixInfo::genRotMat() {
	return rotationMat = glm::rotate(rotation.x,glm::vec3(1,0,0))
										  * glm::rotate(rotation.y,glm::vec3(0,1,0))
										  * glm::rotate(rotation.z,glm::vec3(0,0,1));
}
glm::mat4&  MatrixInfo::genScaleMat() { return scaleMat = glm::scale(scale); }
glm::mat4&  MatrixInfo::genTranslationMat() { return translationMat = glm::translate(position); }
glm::mat4&  MatrixInfo::genCompleteTransform() {
	return transform = preTransform
		* genTranslationMat()
		* genRotMat()
		* genScaleMat()
		* postTransform;
}


void MatrixInfo::setScale(float xyz) {
	scale = glm::vec3(xyz,xyz,xyz);
}