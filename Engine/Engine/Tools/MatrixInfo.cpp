#include "MatrixInfo.h"
#include <glm\gtc\quaternion.hpp>
#include <Engine\Entity\Entity.h>
#include <Engine\IO\Stream.h>

namespace {
	bool Equal(glm::vec3& a, glm::vec3& b) {
		for (uint i = 0; i < a.length(); i++)
		{
			if(a[i] != b[i]) return false;
		}
		return true;
	}
}

void MatrixInfo::lateUpdate() {
	transform = getCompleteTransform();
}
glm::mat4& MatrixInfo::getTransform()     { return getCompleteTransform();     } // save this on in the Shader

glm::mat4&  MatrixInfo::getRotMat() {
	if(!Equal(rot, rot_old)) {
		rotationMat = glm::rotate(rot.x,glm::vec3(1,0,0))
		* glm::rotate(rot.y,glm::vec3(0,1,0))
		* glm::rotate(rot.z,glm::vec3(0,0,1));
	}
	rot_old = rot;
	return rotationMat;
}
glm::mat4&  MatrixInfo::getScaleMat() {
	if(!Equal(scale, scale_old)) scaleMat = glm::scale(scale);
	scale_old = scale;
	return scaleMat;
}
glm::mat4&  MatrixInfo::getTranslationMat() {
	if(!Equal(pos, pos_old)) translationMat = glm::translate(pos);
	pos_old == pos;
	return translationMat;
}
glm::mat4&  MatrixInfo::getCompleteTransform() {
	return transform = getTranslationMat() * getRotMat() * getScaleMat();
}

ShaderUniformPram * MatrixInfo::getUniforms()
{
	return &uniforms[0];
}
int MatrixInfo::numOfUniforms()
{
	return uniforms.size();
}
std::string MatrixInfo::getShaderName()
{
	return "MatrixInfo";
}

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

void MatrixInfo::lookAt(glm::vec3 posToLookAt)
{
	auto lookatMat = glm::lookAt(pos,posToLookAt,glm::vec3(0,1,0));
	pos = glm::vec3(lookatMat * glm::vec4(0,0,0,1));
	auto quat = glm::toQuat( glm::mat3(lookatMat) );
	rot = glm::eulerAngles(quat);

}

bool MatrixInfo::isValid()
{
	//I WAS BORN READY!!!!
	return true;
}

void MatrixInfo::saveValues()
{
	pos_saved   = pos;
	rot_saved   = rot;
	scale_saved = scale;
}

void MatrixInfo::restoreValues()
{
	pos	  = pos_saved;
	rot	  = rot_saved;
	scale = scale_saved;
}

std::vector<std::string> MatrixInfo::getErrors()
{
	return std::vector<std::string>();
}

void MatrixInfo::ChildSave(Stream& s)
{
	glm::vec3 vals[] = {pos,rot,scale};
	s << vals[0] << vals[1] << vals[2];
}

void MatrixInfo::ChildLoad(Stream& s)
{
	glm::vec3 * vals[] = {&pos,&rot,&scale};
	s >> *vals[0] >> *vals[1] >> *vals[2];
}
