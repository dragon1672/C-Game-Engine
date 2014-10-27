#pragma once

#include <ExportHeader.h>
#include <Engine/Entity/Component.h>
#include <glm/glm.hpp>
#include <Engine/Tools/PropertyWrapper.h>

class ENGINE_SHARED CameraComponent : public Component {
	bool perspectiveNeedsUpdate;
	glm::mat4 perspective;
	ShaderUniformPram uniforms[4];
public:
	CameraComponent(const char * name = nullptr);
	bool isActive();
	void setActive();
	PropertyGetSet<int> width;
	PropertyGetSet<int> height;
	PropertyGetSet<float> nearPlane;
	PropertyGetSet<float> farPlane;
	glm::mat4& getWorld2View();
	glm::mat4& getPerspective();

	virtual bool isValid();

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getShaderName();

};