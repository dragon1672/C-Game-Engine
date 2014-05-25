#pragma once

#include <glm/glm.hpp>
#include <math.h>
#include "ExportHeader.h"

struct ENGINE_SHARED Particle {
public:
	static glm::vec3 resetTotalForceValue;
	glm::vec3 vel;
	glm::vec3 pos;
	glm::vec3 momentum;
	float mass;
	float drag;
	glm::vec3 totalForce; // reset and calculated each tick from forces registered

	void init(float drag, float mass=1);
	//adds and resets total force
	void addTotalForce(float dt);
	void update(float dt);
	glm::vec3 getAcc();
};