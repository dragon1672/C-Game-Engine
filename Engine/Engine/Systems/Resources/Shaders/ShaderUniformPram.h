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
	uint location;
	void sendData(ShaderProgram * shader, const void * val);
public:
	const void * cashedPointer;
	
	void init(const char * name, ParameterType type);
	void init(const char * name, ParameterType type, const void * val);
	
	void sendData(ShaderProgram * shader);
};