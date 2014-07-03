#pragma once

#include <ExportHeader.h>
#include <Engine\Renderer\Shader\ShaderUniformPram.h>
#include <Engine\Renderer\Geo\GeometryInfo.h>

#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)

#include "ParameterType.h"

typedef unsigned int uint;

class ENGINE_SHARED Renderable {
private:
	ShaderUniformPram uniformParameters[20];
	uint numUniformParameters;
public:
	GeometryInfo * whatGeo;
	ShaderProgram * howShader;
	glm::mat4 whereMat;
	bool visible;
	uint textureID;

	void init(GeometryInfo * whatGeo, ShaderProgram * howShader, bool visible, uint textureID=-1);
	void reset();

	void addUniformParameter(const char * name, ParameterType parameterType, const float * value);
	void addUniformParameter(const char * name, ParameterType parameterType, const int * value);
	void saveWhereMat(const char * uniformName);
	void saveVisable(const char * uniformName);
	void saveTexture(const char * uniformName);
	void passUniformsDownDown();
};