#include "ShaderUniformPram.h"
#include <Engine/Systems/Resources/ShaderProgram.h>

void ShaderUniformPram::init(const char * name, ParameterType type, const void * val) {
	this->title = name;
	this->type = type;
	cashedPointer = val;
}

ShaderUniformPram::ShaderUniformPram() : cashedPointer(nullptr)
{

}

ShaderUniformPram::ShaderUniformPram(const char * name, ParameterType type, const void * val)
{
	init(name,type,val);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const bool& value)
{
	init(name,ParameterType::PT_BOOLEAN,&value);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const int& value)
{
	init(name,ParameterType::PT_INT,    &value);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const float& value)
{
	init(name,ParameterType::PT_FLOAT,  &value);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const glm::vec3& value)
{
	init(name,ParameterType::PT_VEC3,   &value[0]);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const glm::vec4& value)
{
	init(name,ParameterType::PT_VEC4,   &value[0]);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const glm::mat3& value)
{
	init(name,ParameterType::PT_MAT3,   &value[0][0]);
}

ShaderUniformPram::ShaderUniformPram(const char * name, const glm::mat4& value)
{
	init(name,ParameterType::PT_MAT4,   &value[0][0]);
}
