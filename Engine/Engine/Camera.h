#pragma once

#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)
#include <Windows.h>
#include "ExportHeader.h"

template struct ENGINE_SHARED glm::detail::tvec2<float>;
template struct ENGINE_SHARED glm::detail::tvec3<float>;

class ENGINE_SHARED Camera {
	static glm::vec3 UP;
	glm::vec3 pos;
	glm::vec3 viewDir;
	glm::vec3 strafeDir;

	glm::vec2 oldMousePos;

public:
	Camera()
		: pos(),
		viewDir(0,0,-1) { }
	//void setMovementControls(int moveForward='W', int moveBack='D', int moveLeft=VK_LEFT, int moveRight=VK_RIGHT, int moveUp=VK_UP, int moveDown=VK_DOWN);
	//void setTurnControls(int turnLeft='S', int turnRight='D', int turnUp='Q', int turnDown='E', int activeMouseRotation=' ');
	void setPos(glm::vec3& position, glm::vec3& viewDirection);
	
	
	void moveForward();
	void moveBackward();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void rotate(glm::vec2& change);
	void updateMousePos(const glm::vec2& newMousePos);

	inline glm::vec3 getPos() { return pos; }
	inline glm::vec3 getViewDir() { return viewDir; }

	glm::mat4x4 getWorld2View();
};