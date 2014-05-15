#pragma once

#include "ParticleForceGenerator.h"

class VectorBoundForceGenerator : public ParticleForceGenerator {
	glm::vec3 * bound;
public:
	void init(glm::vec3& toBind) {
		bound = &toBind;
	}
	void updateForce(Particle * ctxt) {
		ctxt->totalForce += *bound;
	}
};