#pragma once

#include <Engine\Entity\Component.h>
#include <Engine\Systems\Resources\Dependencies\GeometryInfo.h>
#include <Engine\Systems\Resources\ShaderProgram.h>
#include <Engine\Systems\Resources\Shaders\ShaderObject.h>
#include <Engine\Systems\Resources\Mesh.h>
#include <ExportHeader.h>

class ENGINE_SHARED RenderableComponent : public Component {
private:
	const char * transformShaderName;
	std::vector<ShaderUniformPram> uniformParameters;
	ShaderUniformPram transform;
public:
	Mesh * whatGeo;
	ShaderProgram * howShader;
	bool visable;

	RenderableComponent(Mesh * geo, ShaderProgram * shader, ShaderUniformPram * uniforms = nullptr, int numOfUniforms = 0)
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
	void addUniformParameter(ShaderObject * obj);
	void addUniformParameter(ShaderUniformPram& obj);

	//convenience to save variables in renderable
	void saveMatrixInfo(const char * uniformName);

	//the real calls
	void addUniformParameter(const char * name, ParameterType parameterType, const void * value);
	

	void update();
	void drawWarmup();
};