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
	int width,height;
	float nearPlane,farPlane;
public:
	CameraComponent(std::string name = "");
	~CameraComponent();
	bool isActive();
	void setActive();

	void  NearPlane(float val) { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != nearPlane; nearPlane = val;  }
	void  FarPlane(float val)  { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != farPlane;  farPlane  = val;  }
	void  Width(int val)       { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != width;     width  = val;     }
	void  Height(int val)      { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != height;    height = val;     }
	float NearPlane() const    { return nearPlane; }
	float FarPlane() const     { return farPlane;  }
	int   Width() const        { return width;     }
	int   Height() const       { return height;    }

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