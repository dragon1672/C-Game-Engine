#pragma once

#include "Particle.h"

class RidgidBody {
public:
	Particle core;
	float rotation;
	glm::vec3 totalTorque;
	float angleVel;
	float totalInertia;
	void update(float dt) {
		core.update(dt);

		glm::vec3 angularAcceleration = (totalTorque/core.mass)*dt;
		angleVel += angularAcceleration.z;

		rotation += angleVel * dt;
	}
};