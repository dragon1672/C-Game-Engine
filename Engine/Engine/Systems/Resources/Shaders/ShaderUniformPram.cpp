#include "ShaderUniformPram.h"
#include <Engine/Systems/Resources/ShaderProgram.h>

void ShaderUniformPram::init(const char * name, ParameterType type) {
	this->title = name;
	this->type = type;
	cashedPointer = nullptr;
}
void ShaderUniformPram::init(const char * name, ParameterType type, const void * val) {
	init(name,type);
	cashedPointer = val;
}

void ShaderUniformPram::sendData(ShaderProgram * shader) {
	if(cashedPointer!=nullptr)   shader->passUniform(title,type,cashedPointer);
}