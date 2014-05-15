#pragma once

#include "ParticleForceGenerator.h"

class GravityForceGenerator : public ParticleForceGenerator {
public:
	glm::vec3 dir;
	void updateForce(Particle * ctxt) {
		ctxt->totalForce += dir;
	}
};