#pragma once

#pragma warning(disable: 4201)
#pragma warning(push)
#include <glm\glm.hpp>
#pragma warning(pop)
#include <Windows.h>
#include <ExportHeader.h>

template struct ENGINE_SHARED glm::detail::tvec2<float>;
template struct ENGINE_SHARED glm::detail::tvec3<float>;

class ENGINE_SHARED Camera {
	static glm::vec3 UP;
	glm::vec3 pos;
	glm::vec3 viewDir;
	glm::vec3 strafeDir;

	glm::vec2 oldMousePos;

public:

	float LARGEST_MOUSE_CHANGE;// = 50;
	float MOUSE_SPEED_SCALE;// = .5f;
	float MOVEMENT_SPEED;// = 1;

	Camera();
	void setPos(glm::vec3& position, glm::vec3& viewDirection);
	void lookAt(glm::vec3& position, glm::vec3& toLookAt);
	
	
	void moveForward(float  dt = 1);
	void moveBackward(float dt = 1);
	void moveLeft(float  dt = 1);
	void moveRight(float dt = 1);
	void moveUp(float   dt = 1);
	void moveDown(float dt = 1);
	void rotate(glm::vec2& change);
	void updateMousePos(const glm::vec2& newMousePos);

	inline glm::vec3& getPos() { return pos; }
	inline glm::vec3 getViewDir() { return viewDir; }

	glm::mat4x4 getWorld2View();
};