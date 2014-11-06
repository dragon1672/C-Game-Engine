#include "MatrixInfo.h"
#include <Engine\Entity\Entity.h>

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
	//if(rot != rot_old)
	{
		rotationMat = glm::toMat4(rot);
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
	pos_old == glm::vec3(pos.x,pos.y,pos.z);
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
	auto lookatMat = glm::lookAt(pos,-posToLookAt,glm::vec3(0,1,0));
	pos = glm::vec3(lookatMat * glm::vec4(0,0,0,1));
	rot = glm::toQuat( glm::mat3(lookatMat) );
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

MatrixInfo::MatrixInfo() : scale(1,1,1)
{
	LUA_OBJECT_START(MatrixInfo);
	uniforms.push_back(ShaderUniformPram("MatrixInfo_TransformMat",  ParameterType::PT_MAT4,  &translationMat[0][0]   ));
	uniforms.push_back(ShaderUniformPram("MatrixInfo_RotationMat",   ParameterType::PT_MAT4,  &rotationMat[0][0]      ));
	uniforms.push_back(ShaderUniformPram("MatrixInfo_ScaleMat",      ParameterType::PT_MAT4,  &scaleMat[0][0]         ));
	uniforms.push_back(ShaderUniformPram("MatrixInfo_Pos",           ParameterType::PT_VEC3,  &pos[0]   ));
	uniforms.push_back(ShaderUniformPram("MatrixInfo_Scale",         ParameterType::PT_VEC3,  &scale[0] ));
	uniforms.push_back(ShaderUniformPram("MatrixInfo_Rotation",      ParameterType::PT_VEC3,  &rot[0]   ));
}

MatrixInfo::~MatrixInfo()
{
	LUA_OBJECT_END(MatrixInfo);
}

void MatrixInfo::setRotation(float angle, glm::vec3 axis)
{
	rot =  glm::normalize(glm::angleAxis(angle, axis));
}

#include <cmath>
void MatrixInfo::addRotation(float angle, glm::vec3 axis)
{
	if(angle == 0) return;
	if ( axis == glm::vec3(0.0f, 1.0f, 0.0f) ) {

		rot =  glm::angleAxis(angle, axis) * rot;
	} else {
		rot = rot * glm::angleAxis(angle, axis);
	}
}


void MatrixInfo::setRotation(float angle, float xAxis, float yAxis, float zAxis)
{
	setRotation(angle,glm::vec3(xAxis,yAxis,zAxis));
}

void MatrixInfo::addRotation(float angle, float xAxis, float yAxis, float zAxis)
{
	addRotation(angle,glm::vec3(xAxis,yAxis,zAxis));
}
