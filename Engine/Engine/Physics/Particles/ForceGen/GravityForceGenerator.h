#pragma once

#include <Engine/Physics/Particles/ParticleForceGenerator.h>

class GravityForceGenerator : public ParticleForceGenerator {
public:
	glm::vec3 dir;
	void updateForce(Particle * ctxt) {
		ctxt->addAcc(dir);
	}
};