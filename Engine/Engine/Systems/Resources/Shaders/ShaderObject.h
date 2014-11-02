#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderUniformPram.h>
#include <string>

class ENGINE_SHARED ShaderObject {
public:
	virtual ShaderUniformPram * getUniforms() { return nullptr; }; // uniform [type] [title]; <- var names are used in shader
	virtual int numOfUniforms() { return 0; };
	virtual std::string getShaderName() { return "404"; }; // #component_name <- put this in the shader to get all the vars
};