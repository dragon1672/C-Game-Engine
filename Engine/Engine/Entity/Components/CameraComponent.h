#pragma once

#include <ExportHeader.h>
#include <Engine/Entity/Component.h>
#include <glm/glm.hpp>
#include <Engine/Tools/Ray.h>
#include <Engine/Tools/MasterLua.h>

class ENGINE_SHARED MAKE_COMPONENT_CLASS(CameraComponent) {
	bool perspectiveNeedsUpdate;
	glm::mat4 perspective;
	glm::mat4 world2View;
	ShaderUniformPram uniforms[6];

	glm::vec3 viewDir;
	glm::vec3 strafeDir;
	int width,height;
	float nearPlane,farPlane;

	void setPosLua(float x, float y, float z);
	void setViewDirLua(float x, float y, float z);
	void lookAtLua(float targetX,float targetY,float targetZ);
	void rotateLua(float pitch, float yaw);
	LUA_OBJECT(CameraComponent);
public:
	CameraComponent(std::string name = "");
	~CameraComponent();
	bool isActive();
	void setActive();

	void  NearPlane(float val);
	void  FarPlane(float val);
	void  Width(int val);
	void  Height(int val);
	float NearPlane() const;
	float FarPlane() const;
	int   Width() const;
	int   Height() const;

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