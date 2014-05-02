#include "Camera.h"
#include <glm\gtx\transform.hpp>

using glm::vec3;
using glm::mat4x4;

const float LARGEST_MOUSE_CHANGE = 50;
const float MOUSE_SPEED_SCALE = .5f;
const float MOVEMENT_SPEED = .5f;

vec3 Camera::UP(0,1,0);

void Camera::setPos(glm::vec3& position, glm::vec3& viewDirection) {
	pos = position;
	viewDir = glm::normalize(viewDirection);
}
mat4x4 Camera::getWorld2View() {
	return glm::lookAt(pos,pos + viewDir,UP);
}

void Camera::moveForward() {
	pos += MOVEMENT_SPEED * viewDir;
}
void Camera::moveBackward() {
	pos -= MOVEMENT_SPEED * viewDir;
}
void Camera::moveLeft() {
	pos -= MOVEMENT_SPEED * strafeDir;
}
void Camera::moveRight() {
	pos += MOVEMENT_SPEED * strafeDir;
}
void Camera::moveUp() {
	pos += MOVEMENT_SPEED * UP;
}
void Camera::moveDown() {
	pos -= MOVEMENT_SPEED * UP;
}
void Camera::rotate(glm::vec2& change) {
	strafeDir= glm::cross(viewDir, UP);
	glm::mat4 mouseRot =  glm::rotate(-change.x, UP)
						* glm::rotate(-change.y, strafeDir);
	viewDir = glm::vec3(mouseRot * glm::vec4(viewDir,1));
}

void Camera::updateMousePos(const glm::vec2& newMousePos) {
	glm::vec2 diff = newMousePos - oldMousePos;
	if(glm::length(diff) < LARGEST_MOUSE_CHANGE)
	{
		glm::vec2 result = MOUSE_SPEED_SCALE*diff;
		rotate(result);
	}
	oldMousePos = newMousePos;
}