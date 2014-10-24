#include "Material.h"



ShaderUniformPram * Material::getUniforms()
{
	return &uniforms[0];
}
int Material::numOfUniforms()
{
	return sizeof(uniforms)/sizeof(*uniforms);
}
std::string Material::getShaderName()
{
	return "Material";
}
