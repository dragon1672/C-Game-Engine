#include "EditorCam.h"
#include <Engine/Systems/InputManager.h>
#include <Engine/Entity/Entity.h>
#include <Engine/Tools/Timer.h>


void EditorCam::update()
{
	float speed = 5;
	if(inputManager.getKeyDown(KeyCode::SHIFT)) speed *= 2.5;
	camManager.ActiveCam(this);
	glm::vec3 viewDir = glm::mat3(parent->getTrans()->getRotMat()) * glm::vec3(0,0,1);
	glm::vec3 strafeDir= glm::normalize(glm::cross(viewDir, glm::vec3(0,1,0)));
	
	if(inputManager.mouse.getMouseButtondown(MouseCodes::MIDDLE_MOUSE)) {
		parent->getTrans()->rot.x +=  inputManager.mouse.delta().y;
		parent->getTrans()->rot.y +=  inputManager.mouse.delta().x;
	}
	auto cross = glm::cross(viewDir,glm::vec3(0,1,0));
	if(inputManager.getKeyDown(KeyCode::W)) Parent()->getTrans()->pos +=  speed * viewDir * Timer::getInstance().deltaTime();
	if(inputManager.getKeyDown(KeyCode::S)) Parent()->getTrans()->pos += -speed * viewDir * Timer::getInstance().deltaTime();
	if(inputManager.getKeyDown(KeyCode::A)) Parent()->getTrans()->pos += -speed * glm::cross(viewDir,glm::vec3(0,1,0)) * Timer::getInstance().deltaTime();
	if(inputManager.getKeyDown(KeyCode::D)) Parent()->getTrans()->pos +=  speed * glm::cross(viewDir,glm::vec3(0,1,0)) * Timer::getInstance().deltaTime();
	if(inputManager.getKeyDown(KeyCode::R)) Parent()->getTrans()->pos +=  speed * glm::vec3(0,1,0) * Timer::getInstance().deltaTime();
	if(inputManager.getKeyDown(KeyCode::F)) Parent()->getTrans()->pos += -speed * glm::vec3(0,1,0) * Timer::getInstance().deltaTime();

}
