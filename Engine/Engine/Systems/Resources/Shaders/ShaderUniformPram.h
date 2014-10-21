#pragma once

#include <Engine\Systems\Resources\Shaders\ParameterType.h>
#include <string>
#include "ExportHeader.h"
#include <Engine\TypeDefs.h>


class ENGINE_SHARED ShaderProgram;

class ENGINE_SHARED ShaderUniformPram {
private:
	ParameterType type;
	const char * title;
	const void * cashedPointer;
public:
	ShaderUniformPram();
	ShaderUniformPram(const char * name, ParameterType type, const void * val);
	inline ParameterType Type()   const { return type; }
	inline const char * Title()   const { return title; }
	inline const void * Pointer() const { return cashedPointer; }
	
	void init(const char * name, ParameterType type, const void * val);
};