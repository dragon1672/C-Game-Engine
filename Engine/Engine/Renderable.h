#pragma once

#include "ShaderUniformPram.h"
#include "GeometryInfo.h"
#include "ExportHeader.h"

#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)

#include "ParameterType.h"

//template struct DLL_SHARED glm::detail::tmat3x3<float>;
//template struct DLL_SHARED glm::detail::tmat4x4<float>;

typedef unsigned int uint;

class ENGINE_SHARED Renderable {
private:
	ShaderUniformPram uniformParameters[5];
	uint numUniformParameters;
public:
	GeometryInfo * whatGeo;
	ShaderProgram * howShader;
	glm::mat4 whereMat;
	glm::mat3 rotation;
	bool visible;
	uint textureID;

	void init(GeometryInfo * whatGeo, ShaderProgram * howShader, bool visible, uint textureID=-1);

	void addUniformParameter(const char * name, ParameterType parameterType, const float * value);
	void addUniformParameter(const char * name, ParameterType parameterType, const int * value);
	void saveWhereMat(const char * uniformName);
	void saveVisable(const char * uniformName);
	void saveTexture(const char * uniformName);
	void passUniformsDownDown();
};