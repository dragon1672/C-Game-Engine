#include "MatrixInfoComponent.h"

void MatrixInfoComponent::lateUpdate() {
	transform = getCompleteTransform();
}
glm::mat4& MatrixInfoComponent::getTransform()     { return getCompleteTransform();     } // save this on in the Shader

glm::mat4&  MatrixInfoComponent::getRotMat() {
	return rotChanged ? rotationMat = glm::rotate(rotation.x,glm::vec3(1,0,0))
										  * glm::rotate(rotation.y,glm::vec3(0,1,0))
										  * glm::rotate(rotation.z,glm::vec3(0,0,1))
										  : rotationMat;
}
glm::mat4&  MatrixInfoComponent::getScaleMat() { return scaleChanged ? scaleMat = glm::scale(scale) : scaleMat; }
glm::mat4&  MatrixInfoComponent::getTranslationMat() { return posChanged ? translationMat = glm::translate(position) : translationMat; }
glm::mat4&  MatrixInfoComponent::getCompleteTransform() {
	return scaleChanged || posChanged || rotChanged ? transform = getTranslationMat() * getRotMat() * getScaleMat() : transform;
}