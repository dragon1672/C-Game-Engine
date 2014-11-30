#include "CameraComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/CameraManager.h>
#include <Engine/IO/Stream.h>
#include <Engine/Tools/Printer.h>

REGISTER_COMPONENT(CameraComponent);

glm::mat4x4& CameraComponent::getWorld2View()
{
	//glm::vec3 tmp = parent->getTrans()->scale;
	//parent->getTrans()->scale = glm::vec3(1,1,1);
	//world2View = parent->getTrans()->getCompleteTransform();
	//parent->getTrans()->scale = tmp;
	//return world2View;
	return world2View = glm::lookAt(Parent()->getTrans()->pos,Parent()->getTrans()->pos + viewDir,glm::vec3(0,1,0));
}

glm::mat4& CameraComponent::getPerspective()
{
	perspectiveNeedsUpdate = perspectiveNeedsUpdate || dims.HasChanged();
	if(perspectiveNeedsUpdate) {
		const float aspectRatio = dims.WidthPixel()/dims.HeightPixel();
		perspective = glm::perspective(60.0f,aspectRatio,(float)nearPlane,(float)farPlane);
	}
	dims.resetChanged();
	perspectiveNeedsUpdate = false;
	return perspective;
}

CameraComponent::CameraComponent(std::string name /*= nullptr*/)
	: active(true), clearColor(.1f,.1f,.1f), Component_CRTP(name)
{
	LUA_OBJECT_START(CameraComponent);
	camManager.allCams.Register(this);

	viewDir = glm::vec3(0,0,-1);
	setPos(glm::vec3(0,0,0));

	perspectiveNeedsUpdate = true;

	NearPlane(.1f);
	FarPlane(100);
	
	uniforms[0] = ShaderUniformPram("nearPlane",   nearPlane   );
	uniforms[1] = ShaderUniformPram("farPlane" ,   farPlane    );
	uniforms[2] = ShaderUniformPram("perspective", perspective );
	uniforms[3] = ShaderUniformPram("world2View",  world2View  );
}

bool CameraComponent::isValid()
{
	//I WAS BORN READY!!!
	return true;
}

ShaderUniformPram * CameraComponent::getUniforms()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CameraComponent::numOfUniforms()
{
	throw std::logic_error("The method or operation is not implemented.");
}

std::string CameraComponent::getShaderName()
{
	return "Camera";
}

Ray CameraComponent::getRayFromMouse(glm::vec2 mp)
{
	glm::vec2 mousePos = mp - dims.StartPixel();
	float x = (2.0f*mousePos.x)/dims.WidthPixel() - 1.0f;
	float y = 1.0f - (2.0f* mousePos.y)/dims.HeightPixel();
	float z = -1.0f;
	
	glm::mat4x4 undoCam = glm::inverse(getWorld2View());
	glm::vec4 temp = glm::inverse(getPerspective() * undoCam) * glm::vec4(x,y,z,0.0);

	Ray ret;

	ret.direction = glm::normalize(glm::vec3(undoCam * glm::vec4(temp.x,temp.y,z,0.0)));
	ret.origin = Parent()->getTrans()->pos;
	return ret;
}

std::vector<std::string> CameraComponent::getErrors()
{
	return std::vector<std::string>();
}

void CameraComponent::ChildSave(Stream& s)
{
	s << nearPlane << farPlane << dims << active; // also save priority
}

void CameraComponent::ChildLoad(Stream& s)
{
	s >> nearPlane >> farPlane >> dims >> active;
	perspectiveNeedsUpdate = true;
}

bool CameraComponent::CopyInto(Component* t)
{
	if(typeid(*t) != typeid(*this)) return false;
	CameraComponent * that = (CameraComponent *)t;
	that->active    = this->active;
	that->farPlane  = this->farPlane;
	that->nearPlane = this->nearPlane;
	that->dims      = this->dims;
	that->perspective = this->perspective;
	return true;
}

CameraComponent::~CameraComponent()
{
	camManager.removeCam(this);
	LUA_OBJECT_END(CameraComponent);
}

void CameraComponent::LUA_lookAt(float targetX,float targetY,float targetZ)
{
	lookAt(glm::vec3(targetX,targetY,targetZ));
}

void CameraComponent::LUA_setViewDir(float x, float y, float z)
{
	viewDir = glm::vec3(x,y,z);
}

void CameraComponent::LUA_setPos(float x, float y, float z)
{
	setPos(glm::vec3(x,y,z));
}

void CameraComponent::NearPlane(float val)
{
	perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != nearPlane; nearPlane = val;
}

float CameraComponent::NearPlane() const
{
	return nearPlane;
}

void CameraComponent::FarPlane(float val)
{
	perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != farPlane;  farPlane  = val;
}

float CameraComponent::FarPlane() const
{
	return farPlane;
}

void CameraComponent::setPos(glm::vec3& position) {
	setPos(position,viewDir);
}
void CameraComponent::setPos(glm::vec3& position, glm::vec3& viewDirection) {
	if(Parent() != nullptr) Parent()->getTrans()->pos = position;
	float lenSquared = glm::dot(viewDirection,viewDirection);
	viewDir = lenSquared > 1 ?
		lenSquared == 0 ? glm::vec3(0,0,-1) : glm::normalize(viewDirection)
		: viewDirection;
	strafeDir= glm::normalize(glm::cross(viewDir, glm::vec3(0,1,0)));
}
void CameraComponent::lookAt(glm::vec3& target)
{
	lookAt(target,Parent()->getTrans()->pos);
}
void CameraComponent::lookAt(glm::vec3& target, glm::vec3& position)
{
	glm::vec3 dir = target - position;
	setPos(position,dir);
}
void CameraComponent::rotate(glm::vec2 pitchYaw)
{
	strafeDir= glm::normalize(glm::cross(viewDir, glm::vec3(0,1,0)));
	glm::mat4 mouseRot =  glm::rotate(-pitchYaw.x, glm::vec3(0,1,0))
		* glm::rotate(-pitchYaw.y, strafeDir);
	viewDir = glm::vec3(mouseRot * glm::vec4(viewDir,1));
}

CameraComponent::operator LuaUserdata<CameraComponent>()
{
	MAKE_LUA_INSTANCE_RET(CameraComponent,ret);

	ret.Bind("rotate",&CameraComponent::LUA_rotate);
	ret.Bind("setPos",&CameraComponent::LUA_setPos);
	ret.Bind("setViewDir",&CameraComponent::LUA_setViewDir);
	ret.Bind("lookAt",&CameraComponent::LUA_lookAt);

	return ret;
}

void CameraComponent::LUA_rotate(float pitch, float yaw)
{
	rotate(glm::vec2(yaw,pitch));
}