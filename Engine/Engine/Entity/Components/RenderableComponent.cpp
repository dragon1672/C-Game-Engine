#include "RenderableComponent.h"
#include <Engine/Entity/Entity.h>

void RenderableComponent::addUniformParameter(const char * name, const bool& value)      { addUniformParameter(name,ParameterType::PT_BOOLEAN,&value);       }
void RenderableComponent::addUniformParameter(const char * name, const float& value)     { addUniformParameter(name,ParameterType::PT_FLOAT,  &value);       }
void RenderableComponent::addUniformParameter(const char * name, const glm::vec3& value) { addUniformParameter(name,ParameterType::PT_VEC3,   &value[0]);    }
void RenderableComponent::addUniformParameter(const char * name, const glm::vec4& value) { addUniformParameter(name,ParameterType::PT_VEC4,   &value[0]);    }
void RenderableComponent::addUniformParameter(const char * name, const glm::mat3& value) { addUniformParameter(name,ParameterType::PT_MAT3,   &value[0][0]); }
void RenderableComponent::addUniformParameter(const char * name, const glm::mat4& value) { addUniformParameter(name,ParameterType::PT_MAT4,   &value[0][0]); }

void RenderableComponent::addUniformParameter(const char * name, ParameterType parameterType, const void * value) {
	uniformParameters.push_back(new ShaderUniformPram());
	uniformParameters[uniformParameters.size()-1]->init(howShader,name,parameterType,value);
}
void RenderableComponent::saveMatrixInfo(const char * uniformName) {
	this->transformShaderName = uniformName;
}

void RenderableComponent::drawWarmup() {
	howShader->useProgram();
	howShader->passSavedUniforms_try();

	if(transformShaderName != nullptr) this->transform.sendData();
	for (uint i = 0; i < uniformParameters.size(); i++) {
		uniformParameters[i]->sendData();
	}
}

void RenderableComponent::update() {
	transform.init(howShader,transformShaderName,ParameterType::PT_MAT4,&parent->getTrans()->getTransform()[0][0]);
}