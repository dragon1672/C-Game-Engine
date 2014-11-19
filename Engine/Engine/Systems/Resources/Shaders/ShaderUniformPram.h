#pragma once

#include <Engine\Systems\Resources\Shaders\ParameterType.h>
#include "ExportHeader.h"
#include <Engine\TypeDefs.h>
#include <glm/glm.hpp>


class ENGINE_SHARED ShaderProgram;

class ENGINE_SHARED ShaderUniformPram {
private:
	ParameterType type;
	const char * title;
	const void * cashedPointer;
public:
	ShaderUniformPram();
	ShaderUniformPram(const char * name, ParameterType type, const void * val);
	ShaderUniformPram(const char * name, const bool& value);
	ShaderUniformPram(const char * name, const int&  value);
	ShaderUniformPram(const char * name, const float& value);
	ShaderUniformPram(const char * name, const glm::vec3& value);
	ShaderUniformPram(const char * name, const glm::vec4& value);
	ShaderUniformPram(const char * name, const glm::mat3& value);
	ShaderUniformPram(const char * name, const glm::mat4& value);
	inline ParameterType Type()   const { return type; }
	inline const char * Title()   const { return title; }
	inline const void * Pointer() const {
		return cashedPointer;
	}
	void Pointer(const void * val) {
		cashedPointer = val;
	}
	
	void init(const char * name, ParameterType type, const void * val);
};