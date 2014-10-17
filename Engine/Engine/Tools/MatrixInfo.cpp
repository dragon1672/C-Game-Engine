#include "MatrixInfo.h"
#include <glm\gtc\quaternion.hpp>

void MatrixInfo::lateUpdate() {
	transform = getCompleteTransform();
}
glm::mat4& MatrixInfo::getTransform()     { return getCompleteTransform();     } // save this on in the Shader

glm::mat4&  MatrixInfo::getRotMat() {
	if(rotChanged) rotationMat = glm::rotate(rot.x,glm::vec3(1,0,0))
		* glm::rotate(rot.y,glm::vec3(0,1,0))
		* glm::rotate(rot.z,glm::vec3(0,0,1));
	rotChanged = false;
	return rotationMat;
}
glm::mat4&  MatrixInfo::getScaleMat() {
	if(scaleChanged) scaleMat = glm::scale(scale);
	scaleChanged = false;
	return scaleMat;
}
glm::mat4&  MatrixInfo::getTranslationMat() {
	if(posChanged) translationMat = glm::translate(pos);
	posChanged = false;
	return translationMat;
}
glm::mat4&  MatrixInfo::getCompleteTransform() {
	return scaleChanged || posChanged || rotChanged ? transform = getTranslationMat() * getRotMat() * getScaleMat() : transform;
}