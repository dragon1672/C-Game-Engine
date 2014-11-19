#pragma once

#include <ExportHeader.h>
#include <Engine/Entity/Component.h>
#include <glm/glm.hpp>
#include <Engine/Tools/PropertyWrapper.h>
#include <Engine/Tools/Ray.h>

class ENGINE_SHARED MAKE_COMPONENT_CLASS(CameraComponent) {
	bool perspectiveNeedsUpdate;
	glm::mat4 perspective;
	glm::mat4 world2View;
	ShaderUniformPram uniforms[6];
public:
	CameraComponent(std::string name = "");
	~CameraComponent();
	bool isActive();
	void setActive();
	PropertyGetSet<int> width;
	PropertyGetSet<int> height;
	PropertyGetSet<float> nearPlane;
	PropertyGetSet<float> farPlane;
	glm::mat4& getWorld2View();
	glm::mat4& getPerspective();

	virtual bool isValid();

	Ray getRayFromMouse(glm::vec2 mousePos);

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getShaderName();

	std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

	virtual bool CopyInto(Component* that);

};