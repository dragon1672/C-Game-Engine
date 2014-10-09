#pragma once

#include <Engine\Entity\Component.h>
#include <Engine\Renderer\Geo\GeometryInfo.h>
#include <Engine\Renderer\Shader\ShaderProgram.h>

class RenderableComponent : public Component {
private:
	const char * transformShaderName;
	std::vector<ShaderUniformPram *> uniformParameters;
	ShaderUniformPram transform;
public:
	GeometryInfo * whatGeo;
	ShaderProgram * howShader;
	bool visable;

	RenderableComponent(GeometryInfo * geo, ShaderProgram * shader, ShaderUniformPram ** uniforms = nullptr, int numOfUniforms = 0)
		: transformShaderName(nullptr), whatGeo(geo), howShader(shader), visable(true) {
			for (int i = 0; i < numOfUniforms; i++)
			{
				uniformParameters.push_back(uniforms[i]);
			}
	}
	
	//convenience overloads
	void addUniformParameter(const char * name, const bool& value);
	void addUniformParameter(const char * name, const float& value);
	void addUniformParameter(const char * name, const glm::vec3& value);
	void addUniformParameter(const char * name, const glm::vec4& value);
	void addUniformParameter(const char * name, const glm::mat3& value);
	void addUniformParameter(const char * name, const glm::mat4& value);

	//convenience to save variables in renderable
	void saveMatrixInfo(const char * uniformName);

	//the real calls
	void addUniformParameter(const char * name, ParameterType parameterType, const void * value);
	

	void update();
	void drawWarmup();
};