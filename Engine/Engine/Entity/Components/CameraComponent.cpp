#include "CameraComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/CameraManager.h>



glm::mat4x4& CameraComponent::getWorld2View()
{
	parent->getTrans()->scale = glm::vec3();
	return parent->getTrans()->getCompleteTransform();
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

CameraComponent::CameraComponent(const char * name /*= nullptr*/)
{
	this->name = name;
	perspectiveNeedsUpdate = true;
	nearPlane.setter = [this](float& val, float&newGuy) { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	farPlane.setter  = [this](float& val, float&newGuy) { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	width.setter     = [this](int& val,   int&newGuy)   { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	height.setter    = [this](int& val,   int&newGuy)   { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	nearPlane = .1f;
	farPlane  = 100;
	
	uniforms[0] = ShaderUniformPram("nearPlane",nearPlane);
	uniforms[1] = ShaderUniformPram("nearPlane",farPlane );
	uniforms[2] = ShaderUniformPram("nearPlane",width    );
	uniforms[3] = ShaderUniformPram("nearPlane",height   );
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
