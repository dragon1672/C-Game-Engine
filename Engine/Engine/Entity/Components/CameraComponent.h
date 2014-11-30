#pragma once

#include <ExportHeader.h>
#include <Engine/Entity/Component.h>
#include <glm/glm.hpp>
#include <Engine/Tools/Ray.h>
#include <Engine/Tools/MasterLua.h>
#include <Engine/Tools/Dims.h>

class ENGINE_SHARED MAKE_COMPONENT_CLASS(CameraComponent) {
	bool perspectiveNeedsUpdate;
	glm::mat4 perspective;
	glm::mat4 world2View;
	ShaderUniformPram uniforms[4];

	glm::vec3 viewDir;
	glm::vec3 strafeDir;
	float nearPlane,farPlane;

	glm::vec2 viewportDims;
	Dims dims;
	bool active;
	

	void LUA_setPos(float x, float y, float z);
	void LUA_setViewDir(float x, float y, float z);
	void LUA_lookAt(float targetX,float targetY,float targetZ);
	void LUA_rotate(float pitch, float yaw);
	LUA_OBJECT(CameraComponent);
public:
	glm::vec3 clearColor;

	CameraComponent(std::string name = "");
	~CameraComponent();
	bool Active() const   { return active; }
	void Active(bool val) { active = val;  }

	Dims * getDims() { return &dims; }
	const Dims getDimsAsPixels()  const { return dims.toPixel();   }
	const Dims getDimsAsPercent() const { return dims.toPercent(); }

	void  NearPlane(float val);
	void  FarPlane(float val);
	float NearPlane() const;
	float FarPlane() const;

	glm::mat4& getWorld2View();
	glm::mat4& getPerspective();

	void setPos(glm::vec3& position);
	void setPos(glm::vec3& position, glm::vec3& viewDirection);
	void lookAt(glm::vec3& target);
	void lookAt(glm::vec3& target,glm::vec3& position);

	void rotate(glm::vec2 pitchYaw);

	virtual bool isValid();

	Ray getRayFromMouse(glm::vec2 mousePos);

	virtual ShaderUniformPram * getUniforms();

	virtual int numOfUniforms();

	virtual std::string getShaderName();

	std::vector<std::string> getErrors();

	virtual void ChildSave(Stream& s);

	virtual void ChildLoad(Stream& s);

	virtual bool CopyInto(Component* that);


	operator LuaUserdata<CameraComponent>();

};