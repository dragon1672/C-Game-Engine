#include "RenderableComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/MatrixInfo.h>
#include <Engine/Systems/Resources/Shaders/ShaderPreProcessor.h>

void RenderableComponent::addUniformParameter(const char * name, const bool& value)      { addUniformParameter(name,ParameterType::PT_BOOLEAN,&value);       }
void RenderableComponent::addUniformParameter(const char * name, const float& value)     { addUniformParameter(name,ParameterType::PT_FLOAT,  &value);       }
void RenderableComponent::addUniformParameter(const char * name, const glm::vec3& value) { addUniformParameter(name,ParameterType::PT_VEC3,   &value[0]);    }
void RenderableComponent::addUniformParameter(const char * name, const glm::vec4& value) { addUniformParameter(name,ParameterType::PT_VEC4,   &value[0]);    }
void RenderableComponent::addUniformParameter(const char * name, const glm::mat3& value) { addUniformParameter(name,ParameterType::PT_MAT3,   &value[0][0]); }
void RenderableComponent::addUniformParameter(const char * name, const glm::mat4& value) { addUniformParameter(name,ParameterType::PT_MAT4,   &value[0][0]); }

void RenderableComponent::addUniformParameter(const char * name, ParameterType parameterType, const void * value) {
	addUniformParameter(ShaderUniformPram(name,parameterType,value));
}

void RenderableComponent::addUniformParameter(ShaderObject * obj)
{
	ShaderPreProcessor::registerShaderObject(obj);
	for (int i = 0; i < obj->numOfUniforms(); i++)
	{
		addUniformParameter(obj->getUniforms()[i]);
	}
}

void RenderableComponent::addUniformParameter(ShaderUniformPram& obj)
{
	uniformParameters.push_back(obj);
}

void RenderableComponent::saveMatrixInfo(const char * uniformName) {
	this->transformShaderName = uniformName;
}

void RenderableComponent::drawWarmup() {
	howShader->useProgram();

	if(transformShaderName != nullptr) howShader->passUniform(transform);
	for (uint i = 0; i < uniformParameters.size(); i++) {
		howShader->passUniform(uniformParameters[i]);
	}
}

void RenderableComponent::update() {
	transform.init(transformShaderName,ParameterType::PT_MAT4,&parent->getTrans()->getTransform()[0][0]);
}