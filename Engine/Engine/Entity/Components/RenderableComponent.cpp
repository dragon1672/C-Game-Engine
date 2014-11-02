#include "RenderableComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/MatrixInfo.h>
#include <Engine/Systems/Resources/Shaders/ShaderPreProcessor.h>

void RenderableComponent::addUniformParameter(const char * name, const bool& value)      { addUniformParameter(name,ParameterType::PT_BOOLEAN,&value);       }
void RenderableComponent::addUniformParameter(const char * name, const int&  value)      { addUniformParameter(name,ParameterType::PT_INT,    &value);       }
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
	objUniforms.push_back(obj);
}

void RenderableComponent::addUniformParameter(ShaderUniformPram& obj)
{
	uniformParameters.push_back(obj);
}

void RenderableComponent::addUniformParameter(ShaderObject& obj)
{
	addUniformParameter(&obj);
}

void RenderableComponent::drawWarmup() {
	shader->useProgram();

	for (uint i = 0; i < uniformParameters.size(); i++) {
		shader->passUniform(uniformParameters[i]);
	}
	for (uint i = 0; i < objUniforms.size(); i++)
	{
		shader->passUniform(objUniforms[i]);
	}
}

bool RenderableComponent::isValid()
{
	return this->shader != nullptr && this->geo != nullptr;
}

RenderableComponent::RenderableComponent(Mesh * geo /*= nullptr*/, ShaderProgram * shader /*= nullptr*/, ShaderUniformPram * uniforms /*= nullptr*/, int numOfUniforms /*= 0*/) : geo(geo), shader(shader), visable(true)
{
	for (int i = 0; i < numOfUniforms; i++)
	{
		uniformParameters.push_back(uniforms[i]);
	}
	addUniformParameter(material);
}

std::vector<std::string> RenderableComponent::getErrors()
{
	std::vector<std::string> ret;
	if(shader == nullptr) ret.push_back("No Shader");
	if(geo    == nullptr) ret.push_back("No Geo");
	return ret;
}
