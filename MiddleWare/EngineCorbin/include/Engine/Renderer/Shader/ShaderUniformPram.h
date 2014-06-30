#pragma once

#include <Engine\Renderer\ParameterType.h>
#include <string>
#include "ExportHeader.h"

typedef unsigned int uint;

class ENGINE_SHARED ShaderProgram;

class ENGINE_SHARED ShaderUniformPram {
private:
	ParameterType type;
	const char * title;
	ShaderProgram * theProg;
public:
	const float * cashedFloat;
	const int * cashedInt;
	const bool * cashedBool;

	void init(ShaderProgram * prog, const char * name, ParameterType type);
	void init(ShaderProgram * prog, const char * name, ParameterType type, const bool * val);
	void init(ShaderProgram * prog, const char * name, ParameterType type, const int * val);
	void init(ShaderProgram * prog, const char * name, ParameterType type, const float * val);

	void sendData();
	void sendData(const bool * val);
	void sendData(const int * val);
	void sendData(const float * val);
};