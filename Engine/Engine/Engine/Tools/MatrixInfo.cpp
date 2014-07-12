#include "MatrixInfo.h"
#include <glm\gtc\quaternion.hpp>

void MatrixInfo::updateMatrix() {
	transform = genCompleteTransform();
}
glm::mat4& MatrixInfo::getTransform()     { return transform;     } // save this on in the Shader

glm::mat4  MatrixInfo::genRotMat() {
	glm::quat rot(rotation);
	return glm::rotate(rotation.x,glm::vec3(1,0,0))
										  * glm::rotate(rotation.y,glm::vec3(0,1,0))
										  * glm::rotate(rotation.z,glm::vec3(0,0,1));
}
glm::mat4  MatrixInfo::genScaleMat() { return glm::scale(scale); }
glm::mat4  MatrixInfo::genTranslationMat() { return glm::translate(position); }
glm::mat4  MatrixInfo::genCompleteTransform() {
	glm::mat4 temp1 = genRotMat();
	glm::mat4 temp2 = genTranslationMat();
	glm::mat4 temp3 = genScaleMat();
	return preTransform
		* genTranslationMat()
		* genRotMat()
		* genScaleMat()
		* postTransform;
}