#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "MyRandom.h"
#include "ExportHeader.h"

class Character;

class ENGINE_SHARED Flag {
public:
	float angle;
	float timeSinceLastMove;
	Character * holder;
	glm::vec3 pos;
	Flag() {
		holder = nullptr;
		transformMat = nullptr;
		changedPosLastFrame = false;
		angle = 0;
		timeSinceLastMove = 0;
	}
	void init(glm::mat4 * transformMat);
	bool hasChangedPos();
	void update(float dt);
	void reset();
private:
	bool changedPosLastFrame;
	glm::mat4 * transformMat;
};