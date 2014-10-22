#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderUniformPram.h>

class ENGINE_SHARED ShaderObject {
public:
	virtual ShaderUniformPram * getUniforms() = 0; // uniform [type] [title]; <- var names are used in shader
	virtual int numOfUniforms() = 0;
	virtual std::string getShaderName() = 0; // #component_name <- put this in the shader to get all the vars
};