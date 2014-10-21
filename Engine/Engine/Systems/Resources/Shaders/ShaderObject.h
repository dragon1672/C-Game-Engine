#pragma once

#include <ExportHeader.h>
#include <Engine/Systems/Resources/Shaders/ShaderUniformPram.h>

class ENGINE_SHARED ShaderObject {
public:
	virtual ShaderUniformPram * getUniforms() = 0;
	virtual int numOfUniforms() = 0;
	virtual std::string getName() = 0;
};