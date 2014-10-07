#include <Engine\Tools\Camera.h>
#include <glm\gtx\transform.hpp>

using glm::vec3;
using glm::mat4x4;

vec3 Camera::UP(0,1,0);

Camera::Camera() {
	pos = glm::vec3();
	viewDir = glm::vec3(0,0,-1);
	enabled = true;
	strafeDir= glm::normalize(glm::cross(viewDir, UP));
	LARGEST_MOUSE_CHANGE = 50;
	MOUSE_SPEED_SCALE = .5f;
	MOVEMENT_SPEED = 30;
}
Camera::Camera(bool enabled) {
	pos = glm::vec3();
	viewDir = glm::vec3(0,0,-1);
	strafeDir= glm::normalize(glm::cross(viewDir, UP));
	LARGEST_MOUSE_CHANGE = 50;
	MOUSE_SPEED_SCALE = .5f;
	MOVEMENT_SPEED = 30;
	this->enabled = enabled;
}

void Camera::setPos(glm::vec3& position, glm::vec3& viewDirection) {
	pos = position;
	float lenSquared = glm::dot(viewDirection,viewDirection);
	viewDir = lenSquared > 1 ?
		lenSquared == 0 ? glm::vec3(0,0,-1) : glm::normalize(viewDirection)
		: viewDirection;
	strafeDir= glm::normalize(glm::cross(viewDir, UP));
}
void Camera::lookAt(glm::vec3& position, glm::vec3& toLookAt) {
	setPos(position,toLookAt - position);
}
mat4x4& Camera::getWorld2View() {
	return lookAtMat = glm::lookAt(pos,pos + viewDir,UP);
}

void Camera::moveForward(float dt) {
	pos += dt * MOVEMENT_SPEED * viewDir;
}
void Camera::moveBackward(float dt) {
	pos -= dt * MOVEMENT_SPEED * viewDir;
}
void Camera::moveLeft(float dt) {
	pos -= dt * MOVEMENT_SPEED * strafeDir;
}
void Camera::moveRight(float dt) {
	pos += dt * MOVEMENT_SPEED * strafeDir;
}
void Camera::moveUp(float dt) {
	pos += dt * MOVEMENT_SPEED * UP;
}
void Camera::moveDown(float dt) {
	pos -= dt * MOVEMENT_SPEED * UP;
}
void Camera::rotate(glm::vec2& change) {
	strafeDir= glm::normalize(glm::cross(viewDir, UP));
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