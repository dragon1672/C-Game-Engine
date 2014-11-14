#pragma once

#include <Engine\Entity\Component.h>
#include <Engine\Systems\Resources\Dependencies\GeometryInfo.h>
#include <Engine\Systems\Resources\ShaderProgram.h>
#include <Engine\Systems\Resources\Shaders\ShaderObject.h>
#include <Engine\Systems\Resources\Mesh.h>
#include <Engine\Systems\Resources\Material.h>
#include <ExportHeader.h>

class ENGINE_SHARED RenderableComponent : public Component {
	double geo;
	double shader;
public:
	std::vector<ShaderUniformPram> uniformParameters;
	std::vector<ShaderObject*> objUniforms;
	Mesh * Geo() {
		return resourceManager.getMesh(geo);
	}
	void Geo(double id) {
		geo = id;
	}
	void Geo(Mesh * data) {
		geo = data != nullptr ? data->getID() : Object::NULL_OBJECT_ID();
	}
	ShaderProgram * Shader() {
		return resourceManager.getShaderProgram(shader);
	}
	void Shader(double id) {
		shader = id;
	}
	void Shader(ShaderProgram * id) {
		shader = id != nullptr ? id->getID() : Object::NULL_OBJECT_ID();
	}

	Material material;
	bool visable;

	RenderableComponent(Mesh * geo = nullptr, ShaderProgram * shader = nullptr, ShaderUniformPram * uniforms = nullptr, int numOfUniforms = 0);
	
	//convenience overloads
	void addUniformParameter(const char * name, const bool& value);
	void addUniformParameter(const char * name, const int&  value);
	void addUniformParameter(const char * name, const float& value);
	void addUniformParameter(const char * name, const glm::vec3& value);
	void addUniformParameter(const char * name, const glm::vec4& value);
	void addUniformParameter(const char * name, const glm::mat3& value);
	void addUniformParameter(const char * name, const glm::mat4& value);
	void addUniformParameter(ShaderObject&  obj);
	void addUniformParameter(ShaderObject * obj);
	void addUniformParameter(ShaderUniformPram& obj);

	//the real calls
	void addUniformParameter(const char * name, ParameterType parameterType, const void * value);

	void drawWarmup();

	virtual bool isValid();

	virtual std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

	virtual bool CopyInto(Component* that);

};