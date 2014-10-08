#pragma once

#include "ParticleForceGenerator.h"

class CheapSpringForceGenerator : public ParticleForceGenerator {
public:
	float springConstent;
	float springRestLength;

	glm::vec3 * anchor;

	void init(float springK, float restLength=1) {
		springConstent = springK;
		springRestLength = restLength;
	}

	//override
	void updateForce(Particle * toUpdate) {
		glm::vec3 diff = *anchor - toUpdate->pos;
		float diffLength = glm::length(diff);
		float magnitude = springConstent * (diffLength - springRestLength);

		glm::vec3 springForce = (diff / diffLength) * magnitude;
		toUpdate->totalForce += springForce;
	}
};