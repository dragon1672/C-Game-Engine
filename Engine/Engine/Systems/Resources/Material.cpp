#include "Material.h"



ShaderUniformPram * Material::getUniforms()
{
	return &uniforms[0];
}
int Material::numOfUniforms()
{
	return uniforms.size();
}
std::string Material::getName()
{
	return "Material";
}
