#include "ShaderUniformPram.h"
#include <Engine/Systems/Resources/ShaderProgram.h>

void ShaderUniformPram::init(const char * name, ParameterType type, const void * val) {
	this->title = name;
	this->type = type;
	cashedPointer = val;
}

void ShaderUniformPram::sendData(ShaderProgram * shader) {
	if(cashedPointer!=nullptr)   shader->passUniform(this);
}

ShaderUniformPram::ShaderUniformPram() : cashedPointer(nullptr)
{

}

ShaderUniformPram::ShaderUniformPram(const char * name, ParameterType type, const void * val)
{
	init(name,type,val);
}
