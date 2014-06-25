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

		glm::vec3 angularAcceleration = (totalTorque/totalInertia)*dt;
		angleVel -= angularAcceleration.z;

		angleVel *= .99;

		rotation += angleVel * dt;
		totalTorque = glm::vec3();
	}
};