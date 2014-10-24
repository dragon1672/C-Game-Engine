#include "CameraComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/CameraManager.h>



glm::mat4x4& CameraComponent::getWorld2View()
{
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
