#pragma once

#include "AStarPath.h"
#include "AStarDebugPath.h"
#include "Renderer.h"
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "State.h"

class Character {
public:
	AStar::DEBUG::DebugPath path;
	glm::mat4 * transformMat;
	float speed;
	glm::vec3 lastPos;
	glm::vec3 direction;
	glm::vec3 pos;
	bool hasFlag;
	State* myState;

	void nextNode();
public:
	void init(glm::mat4 * transformMat) {
		this->transformMat = transformMat;
	}

	glm::vec3 getPos() {
		return pos;
	}

	void update(float dt) {
		myState->update(this);
	}
	glm::mat4x4 getWorld2View() {
		glm::vec3 pos = this->pos;
		pos+=glm::vec3(0,7,0) + 4.0f * direction;
		return glm::lookAt(pos,pos-direction,glm::vec3(0,1,0));
	}
};