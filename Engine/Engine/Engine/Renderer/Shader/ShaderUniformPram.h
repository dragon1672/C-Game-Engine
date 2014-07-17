#pragma once

#include <Engine\Renderer\ParameterType.h>
#include <string>
#include "ExportHeader.h"


class ENGINE_SHARED ShaderProgram;

class ENGINE_SHARED ShaderUniformPram {
private:
	ParameterType type;
	const char * title;
	ShaderProgram * theProg;
public:
	const void * cashedPointer;
	
	void init(ShaderProgram * prog, const char * name, ParameterType type);
	void init(ShaderProgram * prog, const char * name, ParameterType type, const void * val);
	
	void sendData();
	void sendData(const void * val);
};