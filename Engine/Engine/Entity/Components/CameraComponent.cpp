#include "CameraComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/CameraManager.h>
#include <Engine/IO/Stream.h>

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
	if(perspectiveNeedsUpdate) {
		const float aspectRatio = (float)width/(float)height;
		perspective = glm::perspective(60.0f,aspectRatio,(float)nearPlane,(float)farPlane);
	}
	perspectiveNeedsUpdate = false;
	return perspective;
}

CameraComponent::CameraComponent(std::string name /*= nullptr*/)
	: Component_CRTP(name)
{
	
	camManager.allCams.Register(this);
	if(camManager.ActiveCam() == nullptr) camManager.ActiveCam(this);

	viewDir = glm::vec3(0,0,-1);
	setPos(glm::vec3(0,0,0));

	perspectiveNeedsUpdate = true;
	NearPlane(.1f);
	FarPlane(100);
	
	uniforms[0] = ShaderUniformPram("nearPlane",   nearPlane   );
	uniforms[1] = ShaderUniformPram("farPlane" ,   farPlane    );
	uniforms[2] = ShaderUniformPram("width",       width       );
	uniforms[3] = ShaderUniformPram("height",      height      );
	uniforms[4] = ShaderUniformPram("perspective", perspective );
	uniforms[5] = ShaderUniformPram("world2View",  world2View  );
}

bool CameraComponent::isActive()
{
	return camManager.ActiveCam() == this;
}

void CameraComponent::setActive()
{
	camManager.ActiveCam(this);
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

Ray CameraComponent::getRayFromMouse(glm::vec2 mousePos)
{
	float x = (2.0f*mousePos.x)/width - 1.0f;
	float y = 1.0f - (2.0f* mousePos.y)/height;
	float z = -1.0f;

	glm::mat4x4 undoCam = glm::inverse(getWorld2View());
	glm::vec4 temp = glm::inverse(perspective * undoCam) * glm::vec4(x,y,z,0.0);

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
	s << nearPlane << farPlane << width << height;
}

void CameraComponent::ChildLoad(Stream& s)
{
	perspectiveNeedsUpdate = true;
	s >> nearPlane >> farPlane >> width >> height;
}

bool CameraComponent::CopyInto(Component* t)
{
	if(typeid(*t) != typeid(*this)) return false;
	CameraComponent * that = (CameraComponent *)t;
	that->active    = this->active;
	that->farPlane  = this->farPlane;
	that->nearPlane = this->nearPlane;
	that->width     = this->width;
	that->height    = this->height;
	return true;
}

CameraComponent::~CameraComponent()
{
	camManager.removeCam(this);
}

void CameraComponent::lookAtLua(float targetX,float targetY,float targetZ)
{
	lookAt(glm::vec3(targetX,targetY,targetZ));
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

void CameraComponent::Width(int val)
{
	perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != width;     width  = val;
}

int CameraComponent::Width() const
{
	return width;
}

void CameraComponent::Height(int val)
{
	perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != height;    height = val;
}

int CameraComponent::Height() const
{
	return height;
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

