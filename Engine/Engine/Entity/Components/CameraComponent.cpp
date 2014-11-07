#include "CameraComponent.h"
#include <Engine/Entity/Entity.h>
#include <Engine/Systems/CameraManager.h>



glm::mat4x4& CameraComponent::getWorld2View()
{
	glm::vec3 tmp = parent->getTrans()->scale;
	parent->getTrans()->scale = glm::vec3();
	world2View = parent->getTrans()->getCompleteTransform();
	parent->getTrans()->scale = tmp;
	return world2View;
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
	: Component(name)
{
	perspectiveNeedsUpdate = true;
	nearPlane.setter = [this](float& val, float&newGuy) { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	farPlane.setter  = [this](float& val, float&newGuy) { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	width.setter     = [this](int& val,   int&newGuy)   { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	height.setter    = [this](int& val,   int&newGuy)   { perspectiveNeedsUpdate = perspectiveNeedsUpdate || val != newGuy; val = newGuy; };
	nearPlane = .1f;
	farPlane  = 100;
	
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
